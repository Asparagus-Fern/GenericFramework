// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "GenericGameHUDManager.generated.h"

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
class UGenericGameHUDManager : public UWorldSubsystem, public FCoreInternalManager
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

	/* Delegate From UWidgetManager */
private:
	void OnWidgetOpened(FOpenWidgetParameter& Parameter);
	void PostWidgetClosed(UGenericWidget* InWidget);
	
	/* Game HUD */
public:
	WIDGETGENERATION_API void CreateGameHUDs(const TArray<TSoftClassPtr<UGenericGameHUD>>& InGameHUDClasses);
	WIDGETGENERATION_API void CreateGameHUDs(TArray<TSubclassOf<UGenericGameHUD>> InGameHUDClasses);
	WIDGETGENERATION_API void CreateGameHUDs(TArray<UGenericGameHUD*> InGameHUDs);
	WIDGETGENERATION_API void CreateGameHUD(UGenericGameHUD* InGameHUD);
	
	WIDGETGENERATION_API void RemoveGameHUDs(TArray<UGenericGameHUD*> InGameHUDs);
	WIDGETGENERATION_API void RemoveGameHUD(UGenericGameHUD* InGameHUD);

	WIDGETGENERATION_API void ClearGameHUDs();

public:
	inline static FDelegate_HUDDelegate Delegate_PreHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_HUDDelegate BPDelegate_PreHUDCreated;

	inline static FDelegate_OnHUDCreated Delegate_OnHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDCreated BPDelegate_OnHUDCreated;

	inline static FDelegate_HUDDelegate Delegate_PostHUDCreated;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_HUDDelegate BPDelegate_PostHUDCreated;

	inline static FDelegate_OnHUDDestroyed Delegate_OnHUDDestroyed;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDDestroyed BPDelegate_OnHUDDestroyed;

	inline static FDelegate_OnHUDActiveStateChanged Delegate_OnHUDActiveStateChanged;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnHUDActiveStateChanged BPDelegate_OnHUDActiveStateChanged;

protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UGenericGameHUD>> GameHUDs;
};
