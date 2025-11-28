// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "GenericPopupWidgetSubsystem.generated.h"

class UGenericPopupWidget;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericPopupWidgetSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static WIDGETGENERATION_API UGenericPopupWidgetSubsystem* Get(const UObject* WorldContextObject);
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/* Delegate From UGenericWidgetSubsystem */
protected:
	virtual void PostWidgetOpened(UGenericWidget* InWidget);
	virtual void PostWidgetClosed(UGenericWidget* InWidget);

private:
	UPROPERTY()
	TArray<TObjectPtr<UGenericPopupWidget>> BreakGameSlotPopupWidgets;
};
