// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Interface/StateInterface.h"
#include "Obect/GenericObject.h"
#include "PropertyProxy.generated.h"

class UPropertyViewModel;
class UPropertyVisualData;
class UPropertyListItemObject;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI, Blueprintable, EditInlineNew)
class UPropertyProxy : public UGenericObject, public IStateInterface
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API UPropertyProxy(const FObjectInitializer& ObjectInitializer);
	PROPERTYSYSTEM_API virtual void NativeOnCreate() override;
	PROPERTYSYSTEM_API virtual void NativeOnDestroy() override;

public:
	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API TArray<UPropertyViewModel*> GetPropertyViewModels() const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API TArray<UPropertyListItemObject*> GetPropertyListItemObjects() const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API FGameplayTag GetPropertyProxyTag() const;
	PROPERTYSYSTEM_API void SetPropertyProxyTag(FGameplayTag InProxyTag);

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ApplyProperty();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ResetProperty();

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool IsAnyPropertyValueDirty() const;

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void GeneratePropertyListItemObjects(TArray<UPropertyViewModel*>& Result);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyApplied(UPropertyViewModel* InPropertyViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyReset(UPropertyViewModel* InPropertyViewModel);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyChanged(UPropertyViewModel* InPropertyViewModel, EPropertyChangedReason ChangedReason);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UPropertyVisualData> PropertyVisualData = nullptr;

	UPROPERTY(Transient)
	TArray<UPropertyViewModel*> PropertyViewModels;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UPropertyListItemObject>> PropertyListItemObjects;

	UPROPERTY(Transient)
	TArray<UPropertyViewModel*> DirtyPropertyViewModels;

	UPROPERTY()
	FGameplayTag ProxyTag;
};
