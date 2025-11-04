// Copyright ChenTaiye 2025. All Rights Reserved.

#include "K2Node_LoadJsonFileToStruct.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "BPFunctions_Json.h"

void UK2Node_LoadJsonFileToStruct::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	const UClass* Action = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		auto CustomizeLambda = [](UEdGraphNode* NewNode, bool bIsTemplateNode, const FName FunctionName)
		{
			UK2Node_LoadJsonFileToStruct* Node = CastChecked<UK2Node_LoadJsonFileToStruct>(NewNode);
			const UFunction* Function = UBPFunctions_Json::StaticClass()->FindFunctionByName(FunctionName);
			check(Function);
			Node->SetFromFunction(Function);
		};

		UBlueprintNodeSpawner* GetDataNodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(GetDataNodeSpawner != nullptr);
		GetDataNodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeLambda, GET_FUNCTION_NAME_CHECKED(UBPFunctions_Json, LoadJsonFileToStruct));
		ActionRegistrar.AddBlueprintAction(Action, GetDataNodeSpawner);
	}
}

bool UK2Node_LoadJsonFileToStruct::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
	const UEdGraphPin* ValuePin = FindPinChecked(FName("Value"));

	if (MyPin == ValuePin && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)
	{
		if (OtherPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Struct)
		{
			OutReason = TEXT("Value must be a struct.");
			return true;
		}
	}

	return false;
}
