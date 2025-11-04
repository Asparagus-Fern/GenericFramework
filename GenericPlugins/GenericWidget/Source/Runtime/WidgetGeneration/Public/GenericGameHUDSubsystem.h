// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "GenericGameHUDSubsystem.generated.h"

class UGenericWidget;
class UGenericGameHUD;

DECLARE_MULTICAST_DELEGATE(FDelegate_HUDDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBPDelegate_HUDDelegate);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnHUDCreated, UGenericGameHUD*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnHUDCreated, UGenericGameHUD*, InHUD);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnHUDDestroyed, UGenericGameHUD*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnHUDDestroyed, UGenericGameHUD*, InHUD);

DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegate_OnHUDActiveStateChanged, UGenericGameHUD*, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBPDelegate_OnHUDActiveStateChanged, UGenericGameHUD*, InHUD, bool, InActiveState);


/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericGameHUDSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static WIDGETGENERATION_API UGenericGameHUDSubsystem* Get(const UObject* WorldContextObject);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;

	/* Delegate From UWidgetManager */
private:
	void OnWidgetOpened(FOpenWidgetParameter& Parameter);
	void PostWidgetClosed(UGenericWidget* InWidget);

	/* Game HUD */
public:
	WIDGETGENERATION_API void CreateGameHUDs(TArray<UGenericGameHUD*> InGameHUDs);
	WIDGETGENERATION_API void CreateGameHUD(UGenericGameHUD* InGameHUD);

	WIDGETGENERATION_API void RemoveGameHUDs(TArray<UGenericGameHUD*> InGameHUDs);
	WIDGETGENERATION_API void RemoveGameHUD(UGenericGameHUD* InGameHUD);

	WIDGETGENERATION_API void ClearGameHUDs();

public:
	WIDGETGENERATION_API inline static FDelegate_HUDDelegate Delegate_PreHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_HUDDelegate BPDelegate_PreHUDCreated;

	WIDGETGENERATION_API inline static FDelegate_OnHUDCreated Delegate_OnHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDCreated BPDelegate_OnHUDCreated;

	WIDGETGENERATION_API inline static FDelegate_HUDDelegate Delegate_PostHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_HUDDelegate BPDelegate_PostHUDCreated;

	WIDGETGENERATION_API inline static FDelegate_OnHUDDestroyed Delegate_OnHUDDestroyed;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDDestroyed BPDelegate_OnHUDDestroyed;

	WIDGETGENERATION_API inline static FDelegate_OnHUDActiveStateChanged Delegate_OnHUDActiveStateChanged;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDActiveStateChanged BPDelegate_OnHUDActiveStateChanged;

protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UGenericGameHUD>> GameHUDs;
};
