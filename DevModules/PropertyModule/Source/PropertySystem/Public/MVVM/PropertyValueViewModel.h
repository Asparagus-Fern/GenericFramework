// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "PropertyValueViewModel.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, MinimalAPI)
class UPropertyValueViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void Initialize();
	
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void Deinitialize();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	PROPERTYSYSTEM_API void Apply();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	PROPERTYSYSTEM_API void Reverse();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	PROPERTYSYSTEM_API void Reset();

public:
	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API bool GetIsPropertyDirty() const;
	PROPERTYSYSTEM_API void MarkAsPropertyDirty();

private:
	bool bIsPropertyDirty = false;
};
