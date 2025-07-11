// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "UWidget/GameplayTagSlot.h"
#include "GenericWidgetManager.generated.h"

class UGenericHUD;
class UGenericWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_PreWidgetOpened, FOpenWidgetParameter&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_PreWidgetOpened, FOpenWidgetParameter&, Parameter);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWidgetOpened, const FOpenWidgetParameter&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWidgetOpened, const FOpenWidgetParameter&, Parameter);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_PostWidgetOpened, UGenericWidget*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_PostWidgetOpened, UGenericWidget*, InWidget);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_PreWidgetClosed, FCloseWidgetParameter&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_PreWidgetClosed, FCloseWidgetParameter&, Parameter);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWidgetClosed, const FCloseWidgetParameter&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWidgetClosed, const FCloseWidgetParameter&, Parameter);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_PostWidgetClosed, UGenericWidget*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_PostWidgetClosed, UGenericWidget*, InWidget);

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericWidgetManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* IStateInterface */
protected:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* UWidgetManager */
public:
	TArray<UGenericWidget*> GetActivedWidgets() { return Widgets; }

public:
	template <typename T>
	T* OpenUserWidget(TSubclassOf<UGenericWidget> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged())
	{
		if (UGenericWidget* NewWidget = OpenUserWidget(InWidgetClass, OnFinish))
		{
			return Cast<T>(NewWidget);
		}
		return nullptr;
	}

	WIDGETGENERATION_API virtual UGenericWidget* OpenUserWidget(TSubclassOf<UGenericWidget> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	WIDGETGENERATION_API virtual bool OpenUserWidget(UGenericWidget* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	WIDGETGENERATION_API virtual bool OpenUserWidget(FOpenWidgetParameter& Parameter);

	WIDGETGENERATION_API virtual bool CloseUserWidget(FGameplayTag InSlotTag, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	WIDGETGENERATION_API virtual bool CloseUserWidget(UGenericWidget* InWidget, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	WIDGETGENERATION_API virtual bool CloseUserWidget(FCloseWidgetParameter& Parameter);

	virtual void ActiveWidget(FOpenWidgetParameter& Parameter);
	virtual void InactiveWidget(FCloseWidgetParameter& Parameter);

private:
	void OnActiveAnimationPlayFinish(UGenericWidget* InWidget);
	void OnInactiveAnimationPlayFinish(UGenericWidget* InWidget);

public:
	/* Call Before Widget Open, To Collect The Parameter That Open Widget Need */
	inline static FDelegate_PreWidgetOpened Delegate_PreWidgetOpened;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_PreWidgetOpened BPDelegate_PreWidgetOpened;

	/* Call On Widget Open Begin, But Animation Not Finish */
	inline static FDelegate_OnWidgetOpened Delegate_OnWidgetOpened;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWidgetOpened BPDelegate_OnWidgetOpened;

	/* Call After Widget Animation Play Finish, Now Widget Is Totally Visible */
	inline static FDelegate_PostWidgetOpened Delegate_PostWidgetOpened;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_PostWidgetOpened BPDelegate_PostWidgetOpened;

	/* Call Before Widget Close, To Collect The Parameter That Close Widget Need */
	inline static FDelegate_PreWidgetClosed Delegate_PreWidgetClosed;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_PreWidgetClosed BPDelegate_PreWidgetClosed;

	/* Call On Widget Close Begin, But Animation Not Finish */
	inline static FDelegate_OnWidgetClosed Delegate_OnWidgetClosed;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnWidgetClosed BPDelegate_OnWidgetClosed;

	/* Call After Widget Animation Play Finish, Now Widget Is Totally Collapsed */
	inline static FDelegate_PostWidgetClosed Delegate_PostWidgetClosed;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_PostWidgetClosed BPDelegate_PostWidgetClosed;

private:
	/* All Widgets */
	UPROPERTY(Transient)
	TArray<TObjectPtr<UGenericWidget>> Widgets;

	UPROPERTY(Transient)
	TArray<FOpenWidgetParameter> OpenWidgetParameters;

	UPROPERTY(Transient)
	TArray<FCloseWidgetParameter> CloseWidgetParameters;
};
