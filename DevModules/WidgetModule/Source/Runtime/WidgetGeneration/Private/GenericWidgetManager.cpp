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
	if (OpenUserWidget(NewWidget, OnFinish))
	{
		return NewWidget;
	}
	else
	{
		return nullptr;
	}
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

bool UGenericWidgetManager::OpenUserWidget(FOpenWidgetParameter& Parameter)
{
	BROADCAST_UNIFIED_DELEGATE(Delegate_PreWidgetOpened, BPDelegate_PreWidgetOpened, Parameter);

	if (Parameter.IsValid())
	{
		if (Parameter.NeedDestroyOldWidget())
		{
			FOnWidgetActiveStateChanged OnWidgetActiveStateChanged = FOnWidgetActiveStateChanged::CreateLambda(
				[&Parameter, this](UGenericWidget* InWidget)
				{
					Parameter.WidgetToRemove = nullptr;
					ActiveWidget(Parameter);
				}
			);

			FCloseWidgetParameter CloseWidgetParameter;
			CloseWidgetParameter.SlotTag = Parameter.SlotTag;
			CloseWidgetParameter.Slot = Parameter.Slot;
			CloseWidgetParameter.WidgetToHandle = Parameter.WidgetToRemove;
			CloseWidgetParameter.bMarkAsGarbage = true;
			CloseWidgetParameter.OnFinish = OnWidgetActiveStateChanged;

			InactiveWidget(CloseWidgetParameter);
		}
		else
		{
			ActiveWidget(Parameter);
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

bool UGenericWidgetManager::CloseUserWidget(FCloseWidgetParameter& Parameter)
{
	BROADCAST_UNIFIED_DELEGATE(Delegate_PreWidgetClosed, BPDelegate_PreWidgetClosed, Parameter);

	if (Parameter.IsValid())
	{
		InactiveWidget(Parameter);
	}

	GenericLOG(GenericLogUI, Error, TEXT("Close Widget Fail!"))
	return false;
}

void UGenericWidgetManager::ActiveWidget(FOpenWidgetParameter& Parameter)
{
	if (Widgets.Contains(Parameter.WidgetToHandle))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InWidget Is Already Actived"))
		Parameter.OnFinish.ExecuteIfBound(Parameter.WidgetToHandle);
		return;
	}

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetOpened, BPDelegate_OnWidgetOpened, Parameter);

	Parameter.WidgetToHandle->GetOnWidgetActiveAnimationPlayFinish().AddUObject(this, &UGenericWidgetManager::OnActiveAnimationPlayFinish);
	Parameter.WidgetToHandle->NativeOnActived();
	Widgets.Add(Parameter.WidgetToHandle);
	OpenWidgetParameters.Add(Parameter);
}

void UGenericWidgetManager::InactiveWidget(FCloseWidgetParameter& Parameter)
{
	if (!Widgets.Contains(Parameter.WidgetToHandle))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InWidget Is Already Inactived"))
		Parameter.OnFinish.ExecuteIfBound(Parameter.WidgetToHandle);
		return;
	}

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetClosed, BPDelegate_OnWidgetClosed, Parameter);

	Parameter.WidgetToHandle->GetOnWidgetInactiveAnimationPlayFinish().AddUObject(this, &UGenericWidgetManager::OnInactiveAnimationPlayFinish);
	Parameter.WidgetToHandle->NativeOnInactived();
	CloseWidgetParameters.Add(Parameter);
}

void UGenericWidgetManager::OnActiveAnimationPlayFinish(UGenericWidget* InWidget)
{
	InWidget->GetOnWidgetActiveAnimationPlayFinish().RemoveAll(this);
	InWidget->NativeOnActivedFinish();

	FOpenWidgetParameter* WidgetParameter =
		OpenWidgetParameters.FindByPredicate([InWidget](const FOpenWidgetParameter& Parameter)
			{
				return Parameter.WidgetToHandle == InWidget;
			}
		);

	if (WidgetParameter)
	{
		OpenWidgetParameters.Remove(*WidgetParameter);
		WidgetParameter->OnFinish.ExecuteIfBound(WidgetParameter->WidgetToHandle);
		BROADCAST_UNIFIED_DELEGATE(Delegate_PostWidgetOpened, BPDelegate_PostWidgetOpened, WidgetParameter->WidgetToHandle);
	}
}

void UGenericWidgetManager::OnInactiveAnimationPlayFinish(UGenericWidget* InWidget)
{
	InWidget->GetOnWidgetInactiveAnimationPlayFinish().RemoveAll(this);
	InWidget->NativeOnInactivedFinish();

	FCloseWidgetParameter* WidgetParameter =
		CloseWidgetParameters.FindByPredicate([InWidget](const FCloseWidgetParameter& Parameter)
			{
				return Parameter.WidgetToHandle == InWidget;
			}
		);

	if (WidgetParameter)
	{
		CloseWidgetParameters.Remove(*WidgetParameter);

		WidgetParameter->OnFinish.ExecuteIfBound(WidgetParameter->WidgetToHandle);
		BROADCAST_UNIFIED_DELEGATE(Delegate_PostWidgetClosed, BPDelegate_PostWidgetClosed, WidgetParameter->WidgetToHandle);

		if (WidgetParameter->bMarkAsGarbage)
		{
			InWidget->NativeOnDestroy();
			Widgets.Remove(WidgetParameter->WidgetToHandle);
			InWidget->MarkAsGarbage();
		}
	}
}
