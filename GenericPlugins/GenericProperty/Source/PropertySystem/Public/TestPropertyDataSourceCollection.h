// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyProxy.h"
#include "DataSource/PropertyDataSourceCollection.h"
#include "TestPropertyDataSourceCollection.generated.h"

UENUM()
enum class ETestPropertyEnum : uint8
{
	TestEnum1,
	TestEnum2,
	TestEnum3,
	TestEnum4,
};


/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UTestPropertyDataSourceCollection : public UPropertyDataSourceCollection
{
	GENERATED_BODY()

protected:
	virtual void GeneratePropertyViewModels_Implementation(TArray<UPropertyViewModel*>& Result) override;
	virtual void OnPropertyApplied_Implementation(UPropertyViewModel* InPropertyViewModel) override;

protected:
	UPROPERTY()
	bool Test1 = false;

	UPROPERTY()
	int32 Test2 = 0;

	UPROPERTY()
	ETestPropertyEnum Test3 = ETestPropertyEnum::TestEnum1;

	UPROPERTY()
	float Test4 = 0.f;

	UPROPERTY()
	int32 Test5 = 0;
};
