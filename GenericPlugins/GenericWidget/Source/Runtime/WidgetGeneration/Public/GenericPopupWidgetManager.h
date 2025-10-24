// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "Interface/ManagerInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "GenericPopupWidgetManager.generated.h"

class UGenericPopupWidget;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericPopupWidgetManager : public UWorldSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* Delegate From UWidgetManager */
private:
	void PostWidgetOpened(UGenericWidget* InWidget);
	void PostWidgetClosed(UGenericWidget* InWidget);

private:
	UPROPERTY()
	TArray<TObjectPtr<UGenericPopupWidget>> BreakGameSlotPopupWidgets;
};
