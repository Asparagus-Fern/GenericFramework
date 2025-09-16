// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/NamedSlot.h"
#include "PropertyValueSpawner.generated.h"

class UPropertyValueWarning;
class UPropertyViewModel;
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
	PROPERTYSYSTEM_API bool SpawnPropertyWidget(const TSubclassOf<UPropertyValueBase>& InClass, UPropertyViewModel* InViewModel);

	UFUNCTION(BlueprintPure)
	PROPERTYSYSTEM_API UPropertyValueBase* GetPropertyWidget();

private:
	void SpawnPropertyValueWarningWidget(const FText& InWarningText);

protected:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPropertyValueBase> PropertyValueWidgetClass = nullptr;
#endif

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPropertyValueWarning> PropertyWarningClass = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyValueBase> PropertyValueWidget = nullptr;
};
