// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Interface/StateInterface.h"
#include "Obect/GenericObject.h"
#include "PropertyProxy.generated.h"

class UPropertyDataSourceCollection;
class UPropertyViewModel;
class UPropertyVisualData;
class UPropertyListItemObject;

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyProxy : public UGenericObject
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual bool Initialize();
	PROPERTYSYSTEM_API virtual void Deinitialize();

public:
	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API const TArray<UPropertyViewModel*>& GetPropertyViewModels() const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API FGameplayTag GetPropertyProxyTag() const;
	PROPERTYSYSTEM_API void SetPropertyProxyTag(FGameplayTag InProxyTag);

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UPropertyDataSourceCollection* GetPropertyDataSourceCollection();
	PROPERTYSYSTEM_API UPropertyDataSourceCollection* SetPropertyDataSourceCollection(const TSubclassOf<UPropertyDataSourceCollection>& InPropertyDataSourceCollectionClass);
	PROPERTYSYSTEM_API void SetPropertyDataSourceCollection(UPropertyDataSourceCollection* InPropertyDataSourceCollection);

	template <typename T>
	T* GetPropertyDataSourceCollection()
	{
		return Cast<T>(PropertyDataSourceCollection);
	}

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ApplyProperty();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ResetProperty();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SetIsPropertyEditable(bool InIsEditable);

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool IsAnyPropertyValueDirty() const;

protected:
	PROPERTYSYSTEM_API void OnPropertyApplied(UPropertyViewModel* InPropertyViewModel);
	PROPERTYSYSTEM_API void OnPropertyReset(UPropertyViewModel* InPropertyViewModel);
	PROPERTYSYSTEM_API void OnPropertyChanged(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason);

protected:
	UPROPERTY()
	FGameplayTag ProxyTag;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyDataSourceCollection> PropertyDataSourceCollection = nullptr;

	UPROPERTY(Transient)
	TArray<UPropertyViewModel*> PropertyViewModels;

	UPROPERTY(Transient)
	TArray<UPropertyViewModel*> DirtyPropertyViewModels;
};
