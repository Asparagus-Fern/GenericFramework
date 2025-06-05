// Copyright ChenTaiye 2025,. All Rights Reserved.

#include "K2Node_ExternalData.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "BPFunctions_ExternalData.h"
#include "EdGraphSchema_K2.h"

void UK2Node_ExternalData::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	const UClass* Action = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		auto CustomizeLambda = [](UEdGraphNode* NewNode, bool bIsTemplateNode, const FName FunctionName)
		{
			UK2Node_ExternalData* Node = CastChecked<UK2Node_ExternalData>(NewNode);
			const UFunction* Function = UBPFunctions_ExternalData::StaticClass()->FindFunctionByName(FunctionName);
			check(Function);
			Node->SetFromFunction(Function);
		};

		UBlueprintNodeSpawner* GetDataNodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(GetDataNodeSpawner != nullptr);
		GetDataNodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeLambda, GET_FUNCTION_NAME_CHECKED(UBPFunctions_ExternalData, GetData));
		ActionRegistrar.AddBlueprintAction(Action, GetDataNodeSpawner);
	}
}

bool UK2Node_ExternalData::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
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
