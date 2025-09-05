// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "Interface/StateInterface.h"
#include "PropertyProxy.generated.h"

class UPropertyListItemObject;
class UPropertyListItemAsset;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI, Blueprintable, EditInlineNew)
class UPropertyProxy : public UGenericObject, public IStateInterface
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeOnCreate() override;
	PROPERTYSYSTEM_API virtual void NativeOnDestroy() override;

public:
	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API TArray<UPropertyListItemObject*> GetPropertyListItemObjects() const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool ExistPropertyListItemObject(FName PropertyName) const;

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UPropertyListItemObject* GetPropertyListItemObject(FName PropertyName) const;

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ApplyPropertyChanged();

	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void ReversePropertyChanged();

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyApplied();

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnPropertyReversed();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UPropertyListItemAsset> PropertyListItemAsset = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UPropertyListItemObject>> PropertyListItemObjects;
};
