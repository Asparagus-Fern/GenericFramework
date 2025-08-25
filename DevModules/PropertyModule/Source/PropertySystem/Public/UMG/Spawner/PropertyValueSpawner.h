// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/NamedSlot.h"
#include "PropertyValueSpawner.generated.h"

class UPropertyValueViewModel;
class UPropertyValueBase;

/**
 * 
 */
UCLASS(MinimalAPI)
class UPropertyValueSpawner : public UNamedSlot
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual TSharedRef<SWidget> RebuildWidget() override;
	PROPERTYSYSTEM_API virtual void SynchronizeProperties() override;
	PROPERTYSYSTEM_API virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	UFUNCTION(BlueprintCallable)
	PROPERTYSYSTEM_API void SpawnPropertyWidget(const TSubclassOf<UPropertyValueBase>& InClass, UPropertyValueViewModel* InViewModel);

protected:
#if WITH_EDITORONLY_DATA

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPropertyValueBase> PropertyWidgetClass = nullptr;

#endif

	UPROPERTY(Transient)
	TObjectPtr<UPropertyValueBase> PropertyWidget = nullptr;
};
