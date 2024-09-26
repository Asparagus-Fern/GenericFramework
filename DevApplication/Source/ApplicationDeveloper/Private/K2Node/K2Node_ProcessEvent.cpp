// Fill out your copyright notice in the Description page of Project Settings.


#include "K2Node/K2Node_ProcessEvent.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EditorCategoryUtils.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"

#define LOCTEXT_NAMESPACE "K2Node_ProcessEvent"

namespace ProcessEventHelper
{
	const FName TargetPinName = "Target";
	const FName FunctionNamePinName = "FunctionName";
}

void UK2Node_ProcessEvent::AllocateDefaultPins()
{
	// Add Execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	// Add Target pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), ProcessEventHelper::TargetPinName);

	// Add RowName pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Name, ProcessEventHelper::FunctionNamePinName);

	Super::AllocateDefaultPins();
}

FText UK2Node_ProcessEvent::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return Super::GetNodeTitle(TitleType);
}

FText UK2Node_ProcessEvent::GetTooltipText() const
{
	return Super::GetTooltipText();
}

void UK2Node_ProcessEvent::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	if (!Pin)
	{
		return;
	}

	if (Pin->PinName == ProcessEventHelper::TargetPinName)
	{
		UEdGraphPin* RowNamePin = GetFunctionNamePin();
		if (RowNamePin)
		{
			NotifyRefreshNode();
		}
	}
}

void UK2Node_ProcessEvent::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
	
	// static const FName Create_FunctionName = GET_FUNCTION_NAME_CHECKED(UObject, ProcessEvent);
	//
	// UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	// CallCreateNode->FunctionReference.SetExternalMember(Create_FunctionName, UObject::StaticClass());
	// CallCreateNode->AllocateDefaultPins();
	//
	// UEdGraphPin* CallCreateExec = CallCreateNode->GetExecPin();
	//
	// CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CallCreateExec);
}

FSlateIcon UK2Node_ProcessEvent::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = GetNodeTitleColor();
	static FSlateIcon Icon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
	return Icon;
}

void UK2Node_ProcessEvent::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	Super::ReallocatePinsDuringReconstruction(OldPins);
}

void UK2Node_ProcessEvent::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_ProcessEvent::GetMenuCategory() const
{
	return FEditorCategoryUtils::GetCommonCategory(FCommonEditorCategory::Utilities);
}

bool UK2Node_ProcessEvent::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
	return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);
}

void UK2Node_ProcessEvent::EarlyValidation(FCompilerResultsLog& MessageLog) const
{
	Super::EarlyValidation(MessageLog);
}

void UK2Node_ProcessEvent::PreloadRequiredAssets()
{
	Super::PreloadRequiredAssets();
}

void UK2Node_ProcessEvent::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);
}

UEdGraphPin* UK2Node_ProcessEvent::GetTargetPin(const TArray<UEdGraphPin*>* InPinsToSearch) const
{
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;
	UEdGraphPin* Pin = nullptr;

	for (UEdGraphPin* PinToSearch : *PinsToSearch)
	{
		if (PinToSearch && PinToSearch->PinName == ProcessEventHelper::TargetPinName)
		{
			Pin = PinToSearch;
			break;
		}
	}

	check(Pin == nullptr || Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_ProcessEvent::GetFunctionNamePin() const
{
	UEdGraphPin* Pin = FindPinChecked(ProcessEventHelper::FunctionNamePinName);
	check(Pin->Direction == EGPD_Input);
	return Pin;
}

void UK2Node_ProcessEvent::NotifyRefreshNode()
{
	UEdGraph* Graph = GetGraph();
	Graph->NotifyNodeChanged(this);
}

#undef LOCTEXT_NAMESPACE
