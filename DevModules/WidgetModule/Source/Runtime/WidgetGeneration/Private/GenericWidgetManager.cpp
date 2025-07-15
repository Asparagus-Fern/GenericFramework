// Copyright ChenTaiye 2025. All Rights Reserved.


#include "GenericWidgetManager.h"

#include "GenericHUDManager.h"
#include "Base/GenericWidget.h"
#include "Blueprint/UserWidget.h"
#include "Manager/ManagerStatics.h"

/* ==================== UWidgetManager ==================== */

bool UGenericWidgetManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UGenericWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UGenericWidgetManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UGenericWidgetManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);
}

void UGenericWidgetManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);

	for (const auto& ActivedWidget : Widgets)
	{
		ActivedWidget->RemoveFromParent();
		ActivedWidget->NativeOnDestroy();
	}

	Widgets.Reset();
}

UGenericWidget* UGenericWidgetManager::OpenUserWidget(TSubclassOf<UGenericWidget> InWidgetClass, FOnWidgetActiveStateChanged OnFinish)
{
	UGenericWidget* NewWidget = CreateWidget<UGenericWidget>(GetWorld(), InWidgetClass);
	if (!OpenUserWidget(NewWidget, OnFinish))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Open Widget Fail"))
		return nullptr;
	}

	return NewWidget;
}

bool UGenericWidgetManager::OpenUserWidget(UGenericWidget* InWidget, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InWidget Is InValid"))
		return false;
	}

	FOpenWidgetParameter Parameter;
	Parameter.SlotTag = InWidget->SlotTag;
	Parameter.WidgetToHandle = InWidget;
	Parameter.OnFinish = OnFinish;

	return OpenUserWidget(Parameter);
}

bool UGenericWidgetManager::OpenUserWidget(FOpenWidgetParameter& OpenWidgetParameter)
{
	BROADCAST_UNIFIED_DELEGATE(Delegate_PreWidgetOpened, BPDelegate_PreWidgetOpened, OpenWidgetParameter);

	if (OpenWidgetParameter.IsValid())
	{
		if (OpenWidgetParameter.NeedDestroyOldWidget())
		{
			FOnWidgetActiveStateChanged OnWidgetActiveStateChanged = FOnWidgetActiveStateChanged::CreateLambda(
				[&OpenWidgetParameter, this](UGenericWidget* InWidget)
				{
					OpenWidgetParameter.WidgetToRemove = nullptr;
					ActiveWidget(OpenWidgetParameter);
				}
			);

			FCloseWidgetParameter CloseWidgetParameter;
			CloseWidgetParameter.SlotTag = OpenWidgetParameter.SlotTag;
			CloseWidgetParameter.Slot = OpenWidgetParameter.Slot;
			CloseWidgetParameter.WidgetToHandle = OpenWidgetParameter.WidgetToRemove;
			CloseWidgetParameter.bMarkAsGarbage = true;
			CloseWidgetParameter.OnFinish = OnWidgetActiveStateChanged;

			InactiveWidget(CloseWidgetParameter);
		}
		else
		{
			ActiveWidget(OpenWidgetParameter);
		}

		return true;
	}

	GenericLOG(GenericLogUI, Error, TEXT("Open Widget Fail!"))
	return false;
}

bool UGenericWidgetManager::CloseUserWidget(FGameplayTag InSlotTag, bool MarkAsGarbage, FOnWidgetActiveStateChanged OnFinish)
{
	if (!InSlotTag.IsValid())
	{
		GenericLOG(GenericLogUI, Error, TEXT("SlotTag Is InValid"))
		return false;
	}

	FCloseWidgetParameter CloseWidgetParameter;
	CloseWidgetParameter.SlotTag = InSlotTag;
	CloseWidgetParameter.bMarkAsGarbage = MarkAsGarbage;
	CloseWidgetParameter.OnFinish = OnFinish;

	return CloseUserWidget(CloseWidgetParameter);
}

bool UGenericWidgetManager::CloseUserWidget(UGenericWidget* InWidget, bool MarkAsGarbage, FOnWidgetActiveStateChanged OnFinish)
{
	if (!IsValid(InWidget))
	{
		GenericLOG(GenericLogUI, Error, TEXT("InWidget Is InValid"))
		OnFinish.ExecuteIfBound(InWidget);
		return false;
	}

	FCloseWidgetParameter CloseWidgetParameter;
	CloseWidgetParameter.SlotTag = InWidget->SlotTag;
	CloseWidgetParameter.WidgetToHandle = InWidget;
	CloseWidgetParameter.bMarkAsGarbage = MarkAsGarbage;
	CloseWidgetParameter.OnFinish = OnFinish;

	return CloseUserWidget(CloseWidgetParameter);
}

bool UGenericWidgetManager::CloseUserWidget(FCloseWidgetParameter& CloseWidgetParameter)
{
	BROADCAST_UNIFIED_DELEGATE(Delegate_PreWidgetClosed, BPDelegate_PreWidgetClosed, CloseWidgetParameter);

	if (CloseWidgetParameter.IsValid())
	{
		InactiveWidget(CloseWidgetParameter);
	}

	GenericLOG(GenericLogUI, Error, TEXT("Close Widget Fail!"))
	return false;
}

void UGenericWidgetManager::ActiveWidget(FOpenWidgetParameter& OpenWidgetParameter)
{
	if (Widgets.Contains(OpenWidgetParameter.WidgetToHandle))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InWidget Is Already Actived"))
		OpenWidgetParameter.OnFinish.ExecuteIfBound(OpenWidgetParameter.WidgetToHandle);
		return;
	}

	Widgets.Add(OpenWidgetParameter.WidgetToHandle);
	OpenWidgetParameters.Add(OpenWidgetParameter);

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetOpened, BPDelegate_OnWidgetOpened, OpenWidgetParameter);

	OpenWidgetParameter.WidgetToHandle->GetOnWidgetActiveAnimationPlayFinish().AddUObject(this, &UGenericWidgetManager::OnActiveAnimationPlayFinish);
	OpenWidgetParameter.WidgetToHandle->NativeOnActived();
}

void UGenericWidgetManager::InactiveWidget(FCloseWidgetParameter& CloseWidgetParameter)
{
	if (!Widgets.Contains(CloseWidgetParameter.WidgetToHandle))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InWidget Is Already Inactived"))
		CloseWidgetParameter.OnFinish.ExecuteIfBound(CloseWidgetParameter.WidgetToHandle);
		return;
	}

	CloseWidgetParameters.Add(CloseWidgetParameter);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetClosed, BPDelegate_OnWidgetClosed, CloseWidgetParameter);

	CloseWidgetParameter.WidgetToHandle->GetOnWidgetInactiveAnimationPlayFinish().AddUObject(this, &UGenericWidgetManager::OnInactiveAnimationPlayFinish);
	CloseWidgetParameter.WidgetToHandle->NativeOnInactived();
}

void UGenericWidgetManager::OnActiveAnimationPlayFinish(UGenericWidget* InWidget)
{
	InWidget->GetOnWidgetActiveAnimationPlayFinish().RemoveAll(this);
	InWidget->NativeOnActivedFinish();

	if (OpenWidgetParameters.Contains(InWidget))
	{
		FOpenWidgetParameter Parameter = *OpenWidgetParameters.FindByKey(InWidget);

		OpenWidgetParameters.Remove(Parameter);
		Parameter.OnFinish.ExecuteIfBound(Parameter.WidgetToHandle);
		BROADCAST_UNIFIED_DELEGATE(Delegate_PostWidgetOpened, BPDelegate_PostWidgetOpened, Parameter.WidgetToHandle);
	}
}

void UGenericWidgetManager::OnInactiveAnimationPlayFinish(UGenericWidget* InWidget)
{
	InWidget->GetOnWidgetInactiveAnimationPlayFinish().RemoveAll(this);
	InWidget->NativeOnInactivedFinish();

	if (CloseWidgetParameters.Contains(InWidget))
	{
		FCloseWidgetParameter Parameter = *CloseWidgetParameters.FindByKey(InWidget);
		CloseWidgetParameters.Remove(Parameter);

		Parameter.OnFinish.ExecuteIfBound(Parameter.WidgetToHandle);
		BROADCAST_UNIFIED_DELEGATE(Delegate_PostWidgetClosed, BPDelegate_PostWidgetClosed, Parameter.WidgetToHandle);

		if (Parameter.bMarkAsGarbage)
		{
			InWidget->NativeOnDestroy();
			Widgets.Remove(Parameter.WidgetToHandle);
			InWidget->MarkAsGarbage();
		}
	}
}
