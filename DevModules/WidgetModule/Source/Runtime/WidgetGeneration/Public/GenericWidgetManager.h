// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.h"
#include "Base/GenericWidget.h"
#include "Interface/ManagerInterface.h"
#include "Manager/ManagerStatics.h"
#include "Subsystems/WorldSubsystem.h"
#include "GenericWidgetManager.generated.h"

class UGenericGameHUD;
class UGenericWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_PreWidgetOpened, FOpenWidgetParameter&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_PreWidgetOpened, FOpenWidgetParameter&, Parameter);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnWidgetOpened, FOpenWidgetParameter&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnWidgetOpened, FOpenWidgetParameter&, Parameter);

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
class UGenericWidgetManager : public UWorldSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

private:
	void PostHUDCreated();
	
	/* IStateInterface */
protected:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override;

	/* UWidgetManager */
public:
	TArray<UGenericWidget*> GetActivedWidgets() const;

	template <typename T>
	T* GetActiveWidget(FGameplayTag InWidgetTag)
	{
		for (auto& Widget : Widgets)
		{
			if (Widget->SelfTag == InWidgetTag)
			{
				return Cast<T>(Widget);
			}
		}

		return nullptr;
	}

public:
	template <typename T>
	T* OpenGenericWidget(TSubclassOf<UGenericWidget> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged())
	{
		if (UGenericWidget* NewWidget = OpenGenericWidget(InWidgetClass, OnFinish))
		{
			return Cast<T>(NewWidget);
		}
		return nullptr;
	}

	WIDGETGENERATION_API virtual UGenericWidget* OpenGenericWidget(TSubclassOf<UGenericWidget> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	WIDGETGENERATION_API virtual bool OpenGenericWidget(UGenericWidget* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	WIDGETGENERATION_API virtual bool OpenGenericWidget(FOpenWidgetParameter& OpenWidgetParameter);

	WIDGETGENERATION_API virtual bool CloseGenericWidget(FGameplayTag InSlotTag, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	WIDGETGENERATION_API virtual bool CloseGenericWidget(UGenericWidget* InWidget, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged());
	WIDGETGENERATION_API virtual bool CloseGenericWidget(FCloseWidgetParameter& CloseWidgetParameter);

	virtual void ActiveWidget(FOpenWidgetParameter& OpenWidgetParameter);
	virtual void InactiveWidget(FCloseWidgetParameter& CloseWidgetParameter);

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

	UPROPERTY()
	TArray<FOpenWidgetParameter> CacheOpenWidgets;
};

template <typename T>
T* OpenGenericWidget(TSubclassOf<UGenericWidget> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged())
{
	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		if (UGenericWidget* NewWidget = GenericWidgetManager->OpenGenericWidget(InWidgetClass, OnFinish))
		{
			return Cast<T>(NewWidget);
		}
	}
	return nullptr;
}

inline static UGenericWidget* OpenGenericWidget(TSubclassOf<UGenericWidget> InWidgetClass, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged())
{
	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return GenericWidgetManager->OpenGenericWidget(InWidgetClass, OnFinish);
	}
	return nullptr;
}

inline static bool OpenGenericWidget(UGenericWidget* InWidget, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged())
{
	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return GenericWidgetManager->OpenGenericWidget(InWidget, OnFinish);
	}
	return false;
}

inline static bool OpenGenericWidget(FOpenWidgetParameter& OpenWidgetParameter)
{
	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return GenericWidgetManager->OpenGenericWidget(OpenWidgetParameter);
	}
	return false;
}

inline static bool CloseGenericWidget(FGameplayTag InSlotTag, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged())
{
	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return GenericWidgetManager->CloseGenericWidget(InSlotTag, MarkAsGarbage, OnFinish);
	}
	return false;
}

inline static bool CloseGenericWidget(UGenericWidget* InWidget, bool MarkAsGarbage = true, FOnWidgetActiveStateChanged OnFinish = FOnWidgetActiveStateChanged())
{
	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return GenericWidgetManager->CloseGenericWidget(InWidget, MarkAsGarbage, OnFinish);
	}
	return false;
}

inline static bool CloseGenericWidget(FCloseWidgetParameter& CloseWidgetParameter)
{
	if (UGenericWidgetManager* GenericWidgetManager = GetManagerOwner<UGenericWidgetManager>())
	{
		return GenericWidgetManager->CloseGenericWidget(CloseWidgetParameter);
	}
	return false;
}
