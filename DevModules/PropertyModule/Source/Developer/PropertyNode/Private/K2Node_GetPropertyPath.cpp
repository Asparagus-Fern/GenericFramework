// Copyright ChenTaiye 2025. All Rights Reserved.


#include "K2Node_GetPropertyPath.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EdGraphUtilities.h"
#include "KismetCompiledFunctionContext.h"
#include "Kismet2/BlueprintEditorUtils.h"

namespace GetPropertyPathHelper
{
	const FName PropertyPinName = "Property";
	const FName PropertyPathPinName = "PropertyPath";
}

#define LOCTEXT_NAMESPACE "GetPropertyPath"

UK2Node_GetPropertyPath::UK2Node_GetPropertyPath(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UK2Node_GetPropertyPath::AllocateDefaultPins()
{
	UEdGraphNode::FCreatePinParams PropertyPathPinParams;
	PropertyPathPinParams.ContainerType = EPinContainerType::Array;
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_String, GetPropertyPathHelper::PropertyPathPinName, PropertyPathPinParams);

	for (int32 i = 0; i < NumInputs; ++i)
	{
		CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, UObject::StaticClass(), GetPinName(i * 2));
		CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, GetPinName((i * 2) + 1));
	}
}

void UK2Node_GetPropertyPath::PostReconstructNode()
{
	Super::PostReconstructNode();
}

FText UK2Node_GetPropertyPath::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return Super::GetNodeTitle(TitleType);
}

FText UK2Node_GetPropertyPath::GetTooltipText() const
{
	return Super::GetTooltipText();
}

FSlateIcon UK2Node_GetPropertyPath::GetIconAndTint(FLinearColor& OutColor) const
{
	return Super::GetIconAndTint(OutColor);
}

void UK2Node_GetPropertyPath::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);
}

void UK2Node_GetPropertyPath::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	Super::ReallocatePinsDuringReconstruction(OldPins);
}

void UK2Node_GetPropertyPath::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

void UK2Node_GetPropertyPath::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	if (!Context->bIsDebugging)
	{
		FToolMenuSection& Section = Menu->AddSection("K2NodeMakeMap", NSLOCTEXT("K2Nodes", "MakeMapHeader", "MakeMap"));

		if (Context->Pin)
		{
			if (Context->Pin->Direction == EGPD_Input && Context->Pin->ParentPin == nullptr)
			{
				Section.AddMenuEntry(
					"RemovePin",
					LOCTEXT("RemovePin", "Remove key/value pair"),
					LOCTEXT("RemovePinTooltip", "Remove this pin and its corresponding key/value pin"),
					FSlateIcon(),
					FUIAction(
						FExecuteAction::CreateUObject(const_cast<UK2Node_GetPropertyPath*>(this), &UK2Node_GetPropertyPath::RemoveInputPin, const_cast<UEdGraphPin*>(Context->Pin))
					)
				);
			}
		}
		else
		{
			Section.AddMenuEntry(
				"AddPin",
				LOCTEXT("AddPin", "Add key/value pair"),
				LOCTEXT("AddPinTooltip", "Add another pair of key/value pins"),
				FSlateIcon(),
				FUIAction(
					FExecuteAction::CreateUObject(const_cast<UK2Node_GetPropertyPath*>(this), &UK2Node_GetPropertyPath::AddInputPin)
				)
			);
		}
	}
}

bool UK2Node_GetPropertyPath::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
	if (!ensure(OtherPin))
	{
		return true;
	}

	if (UEdGraphSchema_K2::IsExecPin(*OtherPin))
	{
		OutReason = NSLOCTEXT("K2Node", "MakeContainer_InputIsExec", "Cannot make a container with an execution input!").ToString();
		return true;
	}

	return false;
}

void UK2Node_GetPropertyPath::AddInputPin()
{
	FScopedTransaction Transaction(LOCTEXT("AddPinTx", "AddPin"));
	Modify();

	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, UObject::StaticClass(), GetPinName(NumInputs * 2));
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, GetPinName((NumInputs * 2) + 1));
	++NumInputs;

	const bool bIsCompiling = GetBlueprint()->bBeingCompiled;
	if (!bIsCompiling)
	{
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}
}

void UK2Node_GetPropertyPath::RemoveInputPin(UEdGraphPin* Pin)
{
	FScopedTransaction Transaction(LOCTEXT("RemovePinTx", "RemovePin"));
	Modify();

	TFunction<void(UEdGraphPin*)> RemovePinLambda = [this, &RemovePinLambda](UEdGraphPin* PinToRemove)
	{
		for (int32 SubPinIndex = PinToRemove->SubPins.Num() - 1; SubPinIndex >= 0; --SubPinIndex)
		{
			RemovePinLambda(PinToRemove->SubPins[SubPinIndex]);
		}

		int32 PinRemovalIndex = INDEX_NONE;
		if (Pins.Find(PinToRemove, PinRemovalIndex))
		{
			Pins.RemoveAt(PinRemovalIndex);
			PinToRemove->MarkAsGarbage();
		}
	};

	{
		TArray<UEdGraphPin*> KeyPins;
		TArray<UEdGraphPin*> ValuePins;
		GetKeyAndValuePins(KeyPins, ValuePins);

		int32 PinIndex = INDEX_NONE;
		if (ValuePins.Find(Pin, PinIndex))
		{
			RemovePinLambda(KeyPins[PinIndex]);
		}
		else
		{
			verify(KeyPins.Find(Pin, PinIndex));
			RemovePinLambda(ValuePins[PinIndex]);
		}
	}

	RemovePinLambda(Pin);
	PinConnectionListChanged(Pin);

	--NumInputs;
	SyncPinNames();
	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}

FName UK2Node_GetPropertyPath::GetPinName(int32 PinIndex) const
{
	const int32 PairIndex = PinIndex / 2;
	if (PinIndex % 2 == 0)
	{
		return *FString::Printf(TEXT("Key %d"), PairIndex);
	}
	else
	{
		return *FString::Printf(TEXT("Value %d"), PairIndex);
	}
}

void UK2Node_GetPropertyPath::GetKeyAndValuePins(TArray<UEdGraphPin*>& KeyPins, TArray<UEdGraphPin*>& ValuePins) const
{
	for (UEdGraphPin* CurrentPin : Pins)
	{
		if (CurrentPin->Direction == EGPD_Input && CurrentPin->ParentPin == nullptr)
		{
			// Key/Value pins alternate so if this is a map and the counts are even then this is a key
			if (KeyPins.Num() == ValuePins.Num())
			{
				KeyPins.Add(CurrentPin);
			}
			else
			{
				ValuePins.Add(CurrentPin);
			}
		}
	}
	check(KeyPins.Num() == ValuePins.Num());
}

void UK2Node_GetPropertyPath::SyncPinNames()
{
	int32 CurrentNumParentPins = 0;
	for (int32 PinIndex = 0; PinIndex < Pins.Num(); ++PinIndex)
	{
		UEdGraphPin*& CurrentPin = Pins[PinIndex];
		if (CurrentPin->Direction == EGPD_Input &&
			CurrentPin->ParentPin == nullptr)
		{
			const FName OldName = CurrentPin->PinName;
			const FName ElementName = GetPinName(CurrentNumParentPins++);

			CurrentPin->Modify();
			CurrentPin->PinName = ElementName;

			if (CurrentPin->SubPins.Num() > 0)
			{
				const FString OldNameStr = OldName.ToString();
				const FString ElementNameStr = ElementName.ToString();
				FString OldFriendlyName = OldNameStr;
				FString ElementFriendlyName = ElementNameStr;

				// SubPin Friendly Name has an extra space in it so we need to account for that
				OldFriendlyName.InsertAt(1, " ");
				ElementFriendlyName.InsertAt(1, " ");

				for (UEdGraphPin* SubPin : CurrentPin->SubPins)
				{
					FString SubPinFriendlyName = SubPin->PinFriendlyName.ToString();
					SubPinFriendlyName.ReplaceInline(*OldFriendlyName, *ElementFriendlyName);

					SubPin->Modify();
					SubPin->PinName = *SubPin->PinName.ToString().Replace(*OldNameStr, *ElementNameStr);
					SubPin->PinFriendlyName = FText::FromString(SubPinFriendlyName);
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
