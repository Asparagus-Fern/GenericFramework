// Copyright ChenTaiye 2025. All Rights Reserved.

#include "TestPropertyDataSourceCollection.h"

#include "DataSource/PropertyDataSource.h"
#include "MVVM/Data/Multi/BoolPropertyValueViewModel.h"
#include "MVVM/Data/Multi/EnumPropertyValueViewModel.h"
#include "MVVM/Data/Multi/NumberPropertyValueViewModel.h"
#include "MVVM/Data/Scalar/ScalarPropertyValueViewModel.h"

#define GET_TEST_PROPERTY_DATA_SOURCE(GetterName, SetterName) \
UPropertyDataSource::Create \
( \
this, \
GET_FUNCTION_NAME_STRING_CHECKED(UTestPropertyDataSourceCollection, GetterName), \
GET_FUNCTION_NAME_STRING_CHECKED(UTestPropertyDataSourceCollection, SetterName) \
)

void UTestPropertyDataSourceCollection::GeneratePropertyViewModels_Implementation(TArray<UPropertyViewModel*>& Result)
{
	Super::GeneratePropertyViewModels_Implementation(Result);

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("Test 1"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(FText::FromString("Test 1"));
		BoolPropertyValueViewModel->SetPropertyDescription(FText::FromString("Test 1 Description"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_TEST_PROPERTY_DATA_SOURCE(Test1, Test1));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("On"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Off"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("Test 2"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(FText::FromString("Test 2"));
		MultiPropertyValueViewModel->SetPropertyDescription(FText::FromString("Test 2 Description"));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_TEST_PROPERTY_DATA_SOURCE(Test2, Test2));

		MultiPropertyValueViewModel->AddNumberValue(0, FText::FromString("Option A"));
		MultiPropertyValueViewModel->AddNumberValue(1, FText::FromString("Option B"));
		MultiPropertyValueViewModel->AddNumberValue(2, FText::FromString("Option C"));
		MultiPropertyValueViewModel->AddNumberValue(3, FText::FromString("Option D"));
		MultiPropertyValueViewModel->AddNumberValue(4, FText::FromString("Option E"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UEnumPropertyValueViewModel* EnumPropertyValueViewModel = NewObject<UEnumPropertyValueViewModel>(this);
		EnumPropertyValueViewModel->SetPropertyName(TEXT("Test 3"));
		EnumPropertyValueViewModel->SetPropertyDisplayName(FText::FromString("Test 3"));
		EnumPropertyValueViewModel->SetPropertyDescription(FText::FromString("Test 3 Description"));
		EnumPropertyValueViewModel->SetPropertyDataSource(GET_TEST_PROPERTY_DATA_SOURCE(Test3, Test3));

		EnumPropertyValueViewModel->AddEnumValue(ETestPropertyEnum::TestEnum1, FText::FromString("Test Enum 1"));
		EnumPropertyValueViewModel->AddEnumValue(ETestPropertyEnum::TestEnum2, FText::FromString("Test Enum 2"));
		EnumPropertyValueViewModel->AddEnumValue(ETestPropertyEnum::TestEnum3, FText::FromString("Test Enum 3"));
		EnumPropertyValueViewModel->AddEnumValue(ETestPropertyEnum::TestEnum4, FText::FromString("Test Enum 4"));

		Result.Add(EnumPropertyValueViewModel);
	}

	{
		UScalarPropertyValueViewModel* ScalarPropertyValueViewModel = NewObject<UScalarPropertyValueViewModel>(this);
		ScalarPropertyValueViewModel->SetPropertyName(TEXT("Test 4"));
		ScalarPropertyValueViewModel->SetPropertyDisplayName(FText::FromString("Test 4"));
		ScalarPropertyValueViewModel->SetPropertyDescription(FText::FromString("Test 4 Description"));
		ScalarPropertyValueViewModel->SetPropertyDataSource(GET_TEST_PROPERTY_DATA_SOURCE(Test4, Test4));

		Result.Add(ScalarPropertyValueViewModel);
	}

	{
		UScalarPropertyValueViewModel* ScalarPropertyValueViewModel = NewObject<UScalarPropertyValueViewModel>(this);
		ScalarPropertyValueViewModel->SetPropertyName(TEXT("Test 5"));
		ScalarPropertyValueViewModel->SetPropertyDisplayName(FText::FromString("Test 5"));
		ScalarPropertyValueViewModel->SetPropertyDescription(FText::FromString("Test 5 Description"));
		ScalarPropertyValueViewModel->SetPropertyDataSource(GET_TEST_PROPERTY_DATA_SOURCE(Test5, Test5));

		ScalarPropertyValueViewModel->SetIsClampValueRange(true);
		ScalarPropertyValueViewModel->SetValueRange(FVector2D(-10, 10));
		ScalarPropertyValueViewModel->SetValueStep(1.f);

		Result.Add(ScalarPropertyValueViewModel);
	}
}

#undef GET_TEST_PROPERTY_DATA_SOURCE

void UTestPropertyDataSourceCollection::OnPropertyApplied_Implementation(UPropertyViewModel* InPropertyViewModel)
{
	Super::OnPropertyApplied_Implementation(InPropertyViewModel);
	// Save Property With SaveGameSlot Or Other...
}
