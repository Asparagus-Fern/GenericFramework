// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Widget.h"

#include "ScreenWidgetManager.h"
#include "Manager/InteractableWidgetGroupManager.h"
#include "Manager/ManagerProxy.h"
#include "UserWidget/Base/UserWidgetBase.h"

/* ==================== Interactable Widget Group ==================== */

void UBPFunctions_Widget::AddInteractableWidget(UInteractableWidgetBase* InteractableWidget, const FString GroupName)
{
	if (UInteractableWidgetGroupManager* InteractableWidgetGroupManager = UManagerProxy::Get()->GetManager<UInteractableWidgetGroupManager>())
	{
		InteractableWidgetGroupManager->AddInteractableWidget(InteractableWidget, GroupName);
	}
}

void UBPFunctions_Widget::RemoveInteractableWidget(UInteractableWidgetBase* InteractableWidget, const FString GroupName)
{
	if (UInteractableWidgetGroupManager* InteractableWidgetGroupManager = UManagerProxy::Get()->GetManager<UInteractableWidgetGroupManager>())
	{
		InteractableWidgetGroupManager->RemoveInteractableWidget(InteractableWidget, GroupName);
	}
}

void UBPFunctions_Widget::ClearupInteractableWidgetGroup(const FString& GroupName, const bool DeselectAll)
{
	if (UInteractableWidgetGroupManager* InteractableWidgetGroupManager = UManagerProxy::Get()->GetManager<UInteractableWidgetGroupManager>())
	{
		InteractableWidgetGroupManager->ClearupInteractableWidgetGroup(GroupName, DeselectAll);
	}
}

bool UBPFunctions_Widget::GetInteractableWidgetGroups(TMap<FString, UCommonButtonGroup*>& Groups)
{
	if (const UInteractableWidgetGroupManager* InteractableWidgetGroupManager = UManagerProxy::Get()->GetManager<UInteractableWidgetGroupManager>())
	{
		for (auto& InteractableWidgetGroup : InteractableWidgetGroupManager->GetInteractableWidgetGroups())
		{
			Groups.FindOrAdd(InteractableWidgetGroup.Key, InteractableWidgetGroup.Value);
		}
		return true;
	}
	return false;
}

bool UBPFunctions_Widget::FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group)
{
	if (const UInteractableWidgetGroupManager* InteractableWidgetGroupManager = UManagerProxy::Get()->GetManager<UInteractableWidgetGroupManager>())
	{
		return InteractableWidgetGroupManager->FindInteractableWidgetGroup(GroupName, Group);
	}

	return false;
}

/* ==================== Game HUD ==================== */

bool UBPFunctions_Widget::GetGameHUDs(TArray<UGameHUD*>& GameHUDs)
{
	if (const UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		GameHUDs = ScreenWidgetManager->GameHUDs;
		return true;
	}

	return false;
}

bool UBPFunctions_Widget::GetGameHUDByTag(const FGameplayTag InTag, TArray<UGameHUD*>& GameHUDs)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		GameHUDs = ScreenWidgetManager->GetGameHUDByTag(InTag);
		return true;
	}

	return false;
}

void UBPFunctions_Widget::SetAllGameHUDActiveState(const bool IsVisisble)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->SetGameHUDActiveState(IsVisisble);
	}
}

void UBPFunctions_Widget::SetGameHUDActiveState(UGameHUD* GameHUD, const bool IsVisisble)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->SetGameHUDActiveState(GameHUD, IsVisisble);
	}
}

void UBPFunctions_Widget::SetGameHUDActiveStateByTag(const FGameplayTag InTag, const bool IsVisisble)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->SetGameHUDActiveState(InTag, IsVisisble);
	}
}







UUserWidgetBase* UBPFunctions_Widget::GetSlotWidget(FGameplayTag InSlotTag)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		return ScreenWidgetManager->GetSlotWidget(InSlotTag);
	}

	return nullptr;
}

/* ==================== User Widget Base ==================== */

UUserWidgetBase* UBPFunctions_Widget::OpenUserWidgetByClass(const TSubclassOf<UUserWidgetBase> InWidgetClass)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		return ScreenWidgetManager->OpenUserWidget(InWidgetClass);
	}

	return nullptr;
}

void UBPFunctions_Widget::OpenUserWidget(UUserWidgetBase* InWidget)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->OpenUserWidget(InWidget);
	}
}

void UBPFunctions_Widget::CloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->CloseUserWidget(InWidget, FOnWidgetActiveStateChanged(), MarkAsGarbage);
	}
}

void UBPFunctions_Widget::CloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->CloseUserWidget(InSlotTag, FOnWidgetActiveStateChanged(), MarkAsGarbage);
	}
}

void UBPFunctions_Widget::MoveUserWidget(FGameplayTag OriginSlotTag, FGameplayTag TargetSlotTag)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->MoveUserWidget(OriginSlotTag, TargetSlotTag, FOnWidgetActiveStateChanged());
	}
}

bool UBPFunctions_Widget::GetActivedWidgets(TArray<UUserWidgetBase*>& ActivedWidgets)
{
	if (const UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ActivedWidgets = ScreenWidgetManager->ActivedWidgets;
		return true;
	}

	return false;
}

/* ==================== Game Menu ==================== */

void UBPFunctions_Widget::SwitchGameMenu(UGameMenuSetting* InGameMenuSetting)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->SwitchGameMenu(InGameMenuSetting);
	}
}

void UBPFunctions_Widget::SelectMenu(FGameplayTag InMenuTag)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->SelectMenu(InMenuTag);
	}
}

void UBPFunctions_Widget::DeselectMenu(FGameplayTag InMenuTag)
{
	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->DeselectMenu(InMenuTag);
	}
}

UGameMenuSetting* UBPFunctions_Widget::GetGameMenu(const UObject* WorldContextObject)
{
	if (const UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		return ScreenWidgetManager->GameMenu;
	}

	return nullptr;
}

bool UBPFunctions_Widget::GetMenuGenerateInfos(TArray<FMenuGenerateInfo>& MenuGenerateInfos)
{
	if (const UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		MenuGenerateInfos = ScreenWidgetManager->MenuGenerateInfos;
		return true;
	}

	return false;
}
