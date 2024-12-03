// Fill out your copyright notice in the Description page of Project Settings.


#include "K2Node_GetGDALField.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "BPFunctions_GDAL.h"

#define LOCTEXT_NAMESPACE "K2Node_GetGDALField"

UK2Node_GetGDALField::UK2Node_GetGDALField()
{
	FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UBPFunctions_GDAL, GetGDALField), UBPFunctions_GDAL::StaticClass());
}

void UK2Node_GetGDALField::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	/* Structure to hold one-time initialization */
	struct FPinStatics
	{
		int32 InputGDALFeaturePinIndex = -1;
		int32 InputFieldNamePinIndex = -1;

		int32 OutputValuePinIndex = -1;
		int32 OutputResultPinIndex = -1;

		FPinStatics(const TArray<UEdGraphPin*>& InPins)
		{
			InputGDALFeaturePinIndex = FindPinByName(InPins, TEXT("self")); // default name, won't change
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

	const UEdGraphPin* InputGDALFeaturePin = GetPinAt(PinInfo.InputGDALFeaturePinIndex);
	check(InputGDALFeaturePin);

	const UEdGraphPin* InputFieldNamePin = GetPinAt(PinInfo.InputFieldNamePinIndex);
	check(InputFieldNamePin);

	const UEdGraphPin* OutputValuePin = GetPinAt(PinInfo.OutputValuePinIndex);
	check(OutputValuePin);

	const UEdGraphPin* OutputResultPin = GetPinAt(PinInfo.OutputResultPinIndex);
	check(OutputResultPin);
}

FText UK2Node_GetGDALField::GetTooltipText() const
{
	return LOCTEXT("TooltipText", "Get the specified GDAL Field, the type is determined by the output target property.");
}

bool UK2Node_GetGDALField::IsNodePure() const
{
	return false;
}

void UK2Node_GetGDALField::GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const
{
	const UClass* ActionKey = GetClass();
	if (InActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		InActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_GetGDALField::GetMenuCategory() const
{
	static FText MenuCategory = LOCTEXT("MenuCategory", "GDAL");
	return MenuCategory;
}

#undef LOCTEXT_NAMESPACE
