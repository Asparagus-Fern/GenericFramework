// Copyright ChenTaiye 2025. All Rights Reserved.

#include "K2Node_TryGetJsonField.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "BPFunctions_Json.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "FGenericJsonNodeModule"

UK2Node_TryGetJsonField::UK2Node_TryGetJsonField()
{
	FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UBPFunctions_Json, GetJsonField), UBPFunctions_Json::StaticClass());
}

void UK2Node_TryGetJsonField::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	/* Structure to hold one-time initialization */
	struct FPinStatics
	{
		int32 InputJsonObjectPinIndex = -1;
		int32 InputFieldNamePinIndex = -1;
		int32 InputArrayIndexPinIndex = -1;

		int32 OutputValuePinIndex = -1;
		int32 OutputResultPinIndex = -1;

		FPinStatics(const TArray<UEdGraphPin*>& InPins)
		{
			InputJsonObjectPinIndex = FindPinByName(InPins, TEXT("self")); // default name, won't change
			InputFieldNamePinIndex = FindPinByName(InPins, TEXT("FieldName"));

			OutputValuePinIndex = FindPinByName(InPins, TEXT("OutValue"));
			OutputResultPinIndex = FindPinByName(InPins, TEXT("ReturnValue")); // default name, won't change
		}

		static int32 FindPinByName(const TArray<UEdGraphPin*>& InPins, const FName& InName)
		{
			return InPins.IndexOfByPredicate([&InName](const UEdGraphPin* InPin)
				{
					return InPin->GetFName() == InName;
				}
			);
		}
	};
	static FPinStatics PinInfo(Pins);

	const UEdGraphPin* InputJsonObjectPin = GetPinAt(PinInfo.InputJsonObjectPinIndex);
	check(InputJsonObjectPin);

	const UEdGraphPin* InputFieldNamePin = GetPinAt(PinInfo.InputFieldNamePinIndex);
	check(InputFieldNamePin);

	const UEdGraphPin* OutputValuePin = GetPinAt(PinInfo.OutputValuePinIndex);
	check(OutputValuePin);

	const UEdGraphPin* OutputResultPin = GetPinAt(PinInfo.OutputResultPinIndex);
	check(OutputResultPin);
}

FText UK2Node_TryGetJsonField::GetTooltipText() const
{
	return LOCTEXT("TooltipText", "Get the specified Json Field, the type is determined by the output target property.");
}

bool UK2Node_TryGetJsonField::IsNodePure() const
{
	return false;
}

void UK2Node_TryGetJsonField::GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const
{
	Super::GetMenuActions(InActionRegistrar);

	const UClass* Action = GetClass();
	if (InActionRegistrar.IsOpenForRegistration(Action))
	{
		auto CustomizeLambda = [](UEdGraphNode* NewNode, bool bIsTemplateNode, const FName FunctionName)
		{
			UK2Node_TryGetJsonField* Node = CastChecked<UK2Node_TryGetJsonField>(NewNode);
			const UFunction* Function = UBPFunctions_Json::StaticClass()->FindFunctionByName(FunctionName);
			check(Function);
			Node->SetFromFunction(Function);
		};

		UBlueprintNodeSpawner* GetDataNodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(GetDataNodeSpawner != nullptr);
		GetDataNodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeLambda, GET_FUNCTION_NAME_CHECKED(UBPFunctions_Json, GetJsonField));
		InActionRegistrar.AddBlueprintAction(Action, GetDataNodeSpawner);
	}
}

FText UK2Node_TryGetJsonField::GetMenuCategory() const
{
	static FText MenuCategory = LOCTEXT("MenuCategory", "Json");
	return MenuCategory;
}

void UK2Node_TryGetJsonField::NotifyInputChanged() const
{
	if (UBlueprint* BP = GetBlueprint())
	{
		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
	}

	UEdGraph* Graph = GetGraph();
	Graph->NotifyNodeChanged(this);
}

#undef LOCTEXT_NAMESPACE
