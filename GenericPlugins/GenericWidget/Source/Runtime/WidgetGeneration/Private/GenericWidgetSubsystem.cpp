// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericWidgetSubsystem.h"

#include "GenericGameHUDSubsystem.h"
#include "WidgetSettings.h"
#include "Base/GenericWidget.h"
#include "Blueprint/WidgetTree.h"
#include "StaticFunctions/StaticFunctions_Object.h"

#include "Type/GenericType.h"

/* ==================== UGenericWidgetSubsystem ==================== */

UGenericWidgetSubsystem* UGenericWidgetSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

bool UGenericWidgetSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && !IsRunningDedicatedServer();
}

void UGenericWidgetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UGenericGameHUDSubsystem::Delegate_PostHUDCreated.AddUObject(this, &UGenericWidgetSubsystem::PostHUDCreated);
}

void UGenericWidgetSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UGenericGameHUDSubsystem::Delegate_PostHUDCreated.RemoveAll(this);
}

void UGenericWidgetSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
	Super::OnWorldBeginTearDown(InWorld);

	for (const auto& ActivedWidget : Widgets)
	{
		ActivedWidget->RemoveFromParent();
		ActivedWidget->NativeOnDestroy();
	}

	Widgets.Reset();
}

void UGenericWidgetSubsystem::PostHUDCreated()
{
	for (const auto& WidgetSoftClass : UWidgetSettings::Get()->WidgetClasses)
	{
		if (TSubclassOf<UGenericWidget> WidgetClass = FStaticFunctions_Object::LoadClass<UGenericWidget>(WidgetSoftClass))
		{
			UGenericWidget* NewWidget = CreateWidget<UGenericWidget>(GetWorld(), WidgetClass);
			OpenGenericWidget(NewWidget);
		}
	}
}

UGenericWidget* UGenericWidgetSubsystem::GetActivedWidget(FGameplayTag InTag) const
{
	for (auto& ActivedWidget : Widgets)
	{
		if (ActivedWidget->SelfTag == InTag)
		{
			return ActivedWidget;
		}
	}
	return nullptr;
}

TArray<UGenericWidget*> UGenericWidgetSubsystem::GetActivedWidgets() const
{
	return Widgets;
}

bool UGenericWidgetSubsystem::OpenGenericWidget(UGenericWidget* InWidget, const FOnWidgetActiveStateChanged& OnFinish)
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

	return OpenGenericWidget(Parameter);
}

bool UGenericWidgetSubsystem::OpenGenericWidget(FOpenWidgetParameter& OpenWidgetParameter)
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

bool UGenericWidgetSubsystem::CloseGenericWidget(FGameplayTag InSlotTag, bool MarkAsGarbage, const FOnWidgetActiveStateChanged& OnFinish)
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

	return CloseGenericWidget(CloseWidgetParameter);
}

bool UGenericWidgetSubsystem::CloseGenericWidget(UGenericWidget* InWidget, bool MarkAsGarbage, const FOnWidgetActiveStateChanged& OnFinish)
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

	return CloseGenericWidget(CloseWidgetParameter);
}

bool UGenericWidgetSubsystem::CloseGenericWidget(FCloseWidgetParameter& CloseWidgetParameter)
{
	BROADCAST_UNIFIED_DELEGATE(Delegate_PreWidgetClosed, BPDelegate_PreWidgetClosed, CloseWidgetParameter);

	if (CloseWidgetParameter.IsValid())
	{
		InactiveWidget(CloseWidgetParameter);
		return true;
	}

	GenericLOG(GenericLogUI, Error, TEXT("Close Widget Fail!"))
	return false;
}

void UGenericWidgetSubsystem::ActiveWidget(FOpenWidgetParameter& OpenWidgetParameter)
{
	OpenWidgetParameter.WidgetToHandle->NativeOnCreate();

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetOpened, BPDelegate_OnWidgetOpened, OpenWidgetParameter);

	if (OpenWidgetParameter.bOpenResult)
	{
		if (!Widgets.Contains(OpenWidgetParameter.WidgetToHandle))
		{
			Widgets.Add(OpenWidgetParameter.WidgetToHandle);
		}

		OpenWidgetParameters.Add(OpenWidgetParameter);

		OpenWidgetParameter.WidgetToHandle->GetOnWidgetActiveAnimationPlayFinish().AddUObject(this, &UGenericWidgetSubsystem::OnActiveAnimationPlayFinish);
		OpenWidgetParameter.WidgetToHandle->SetIsActived(true);
	}
	else
	{
		GenericLOG(GenericLogUI, Warning, TEXT("Fail To Open Widget : %s"), *OpenWidgetParameter.WidgetToHandle->GetName())
		CloseGenericWidget(OpenWidgetParameter.WidgetToHandle);
	}
}

void UGenericWidgetSubsystem::InactiveWidget(FCloseWidgetParameter& CloseWidgetParameter)
{
	if (!Widgets.Contains(CloseWidgetParameter.WidgetToHandle))
	{
		GenericLOG(GenericLogUI, Warning, TEXT("InWidget Is Already Inactived"))
		CloseWidgetParameter.OnFinish.ExecuteIfBound(CloseWidgetParameter.WidgetToHandle);
		return;
	}

	CloseWidgetParameters.Add(CloseWidgetParameter);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnWidgetClosed, BPDelegate_OnWidgetClosed, CloseWidgetParameter);

	CloseWidgetParameter.WidgetToHandle->GetOnWidgetInactiveAnimationPlayFinish().AddUObject(this, &UGenericWidgetSubsystem::OnInactiveAnimationPlayFinish);
	CloseWidgetParameter.WidgetToHandle->SetIsActived(false);
}

void UGenericWidgetSubsystem::DestroyWidget()
{
	DestroyTimer.Invalidate();

	for (auto& GarbageWidget : GarbageWidgets)
	{
		GarbageWidget->MarkAsGarbage();
	}

	GarbageWidgets.Reset();
}

void UGenericWidgetSubsystem::OnActiveAnimationPlayFinish(UGenericWidget* InWidget)
{
	InWidget->GetOnWidgetActiveAnimationPlayFinish().RemoveAll(this);

	if (OpenWidgetParameters.Contains(InWidget))
	{
		FOpenWidgetParameter Parameter = *OpenWidgetParameters.FindByKey(InWidget);
		OpenWidgetParameters.Remove(Parameter);

		BROADCAST_UNIFIED_DELEGATE(Delegate_PostWidgetOpened, BPDelegate_PostWidgetOpened, Parameter.WidgetToHandle);
		Parameter.OnFinish.ExecuteIfBound(Parameter.WidgetToHandle);
	}
}

void UGenericWidgetSubsystem::OnInactiveAnimationPlayFinish(UGenericWidget* InWidget)
{
	InWidget->GetOnWidgetInactiveAnimationPlayFinish().RemoveAll(this);

	if (CloseWidgetParameters.Contains(InWidget))
	{
		FCloseWidgetParameter Parameter = *CloseWidgetParameters.FindByKey(InWidget);
		CloseWidgetParameters.Remove(Parameter);

		if (Parameter.bMarkAsGarbage)
		{
			InWidget->NativeOnDestroy();
			Widgets.Remove(Parameter.WidgetToHandle);
			GarbageWidgets.Add(InWidget);
			DestroyTimer = GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &UGenericWidgetSubsystem::DestroyWidget));
		}

		BROADCAST_UNIFIED_DELEGATE(Delegate_PostWidgetClosed, BPDelegate_PostWidgetClosed, Parameter.WidgetToHandle);
		Parameter.OnFinish.ExecuteIfBound(Parameter.WidgetToHandle);
	}
}
