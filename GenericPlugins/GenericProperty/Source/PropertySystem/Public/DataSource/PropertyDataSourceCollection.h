// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Obect/GenericObject.h"
#include "PropertyDataSourceCollection.generated.h"

class UPropertyViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI, Blueprintable)
class UPropertyDataSourceCollection : public UGenericObject
{
	GENERATED_BODY()

	friend class UPropertyProxy;

public:
	UFUNCTION(BlueprintPure)
	UPropertyProxy* GetOwnerPropertyProxy() const;
	void SetOwnerPropertyProxy(UPropertyProxy* InProxy);

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void GeneratePropertyViewModels(TArray<UPropertyViewModel*>& Result);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyApplied(UPropertyViewModel* InPropertyViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyReset(UPropertyViewModel* InPropertyViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyChanged(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason);

private:
	UPROPERTY()
	TWeakObjectPtr<UPropertyProxy> OwnerPropertyProxy = nullptr;
};
