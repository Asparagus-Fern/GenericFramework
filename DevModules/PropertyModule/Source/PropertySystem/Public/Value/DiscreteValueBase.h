// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "DiscreteValueBase.generated.h"

class UDiscreteValueViewModel;
class UDiscreteValuesViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UDiscreteValueBase : public UGenericWidget
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void HandleOnDiscreteValueAdded(UDiscreteValueViewModel* Item);

	UFUNCTION()
	void HandleOnDiscreteValueRemoved(UDiscreteValueViewModel* Item);

	FDelegateHandle OnCurrentValueIndexChangedHandle;
	virtual void OnCurrentValueIndexChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnDiscreteValueAdded(UDiscreteValueViewModel* Item);

	UFUNCTION(BlueprintNativeEvent)
	void OnDiscreteValueRemoved(UDiscreteValueViewModel* Item);

	UFUNCTION(BlueprintNativeEvent)
	void OnDiscreteValueChanged();

protected:
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = "true"))
	TObjectPtr<UDiscreteValuesViewModel> DiscreteValuesViewModel = nullptr;
};
