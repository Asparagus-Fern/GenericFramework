// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Widget.h"

#include "ScreenWidgetManager.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Debug/DebugType.h"
#include "Engine/Texture2DDynamic.h"
#include "Manager/ManagerGlobal.h"
#include "Slate/SlateBrushAsset.h"
#include "UserWidget/Base/UserWidgetBase.h"

TArray<UWidget*> UBPFunctions_Widget::BP_FindWidgets(UUserWidget* InWidget, TSubclassOf<UWidget> InClass)
{
	ensure(InClass);
	return FindWidgets<UWidget>(InWidget);
}

TArray<UGameHUD*> UBPFunctions_Widget::GetGameHUD()
{
	return GetManager<UScreenWidgetManager>()->GetGameHUD();
}

TArray<UGameHUD*> UBPFunctions_Widget::GetGameHUDByTag(const FGameplayTag InTag)
{
	return GetManager<UScreenWidgetManager>()->GetGameHUDByTag(InTag);
}

void UBPFunctions_Widget::SetGameHUDVisibility(const bool IsVisisble)
{
	GetManager<UScreenWidgetManager>()->SetGameHUDVisibility(IsVisisble);
}

UUserWidgetBase* UBPFunctions_Widget::CreateUserWidget(const TSubclassOf<UUserWidgetBase> InWidgetClass)
{
	ensure(InWidgetClass);
	return GetManager<UScreenWidgetManager>()->CreateUserWidget(InWidgetClass);
}

UUserWidgetBase* UBPFunctions_Widget::OpenUserWidgetByClass(const TSubclassOf<UUserWidgetBase> InWidgetClass, FUserWidgetBaseDelegate OnFinish)
{
	ensure(InWidgetClass);

	FSimpleMulticastDelegate OnOpenFinish;
	OnOpenFinish.AddLambda([OnFinish]()
		{
			OnFinish.ExecuteIfBound();
		}
	);

	return GetManager<UScreenWidgetManager>()->OpenUserWidget(InWidgetClass, OnOpenFinish);
}

void UBPFunctions_Widget::OpenUserWidgets(const TArray<UUserWidgetBase*> InWidgets)
{
	GetManager<UScreenWidgetManager>()->OpenUserWidget(InWidgets);
}

void UBPFunctions_Widget::OpenUserWidget(UUserWidgetBase* InWidget, FUserWidgetBaseDelegate OnFinish)
{
	FSimpleMulticastDelegate OnOpenFinish;
	OnOpenFinish.AddLambda([OnFinish]()
		{
			OnFinish.ExecuteIfBound();
		}
	);

	GetManager<UScreenWidgetManager>()->OpenUserWidget(InWidget, OnOpenFinish);
}

void UBPFunctions_Widget::CloseUserWidget(const UUserWidgetBase* InWidget, const FUserWidgetBaseDelegate& OnFinish)
{
	FSimpleMulticastDelegate OnCloseFinish;
	OnCloseFinish.AddLambda([OnFinish]()
		{
			OnFinish.ExecuteIfBound();
		}
	);

	GetManager<UScreenWidgetManager>()->CloseUserWidget(InWidget, OnCloseFinish);
}

void UBPFunctions_Widget::CloseUserWidgetByTag(const FGameplayTag InSlotTag, FUserWidgetBaseDelegate OnFinish)
{
	FSimpleMulticastDelegate OnCloseFinish;
	OnCloseFinish.AddLambda([OnFinish]()
		{
			OnFinish.ExecuteIfBound();
		}
	);

	GetManager<UScreenWidgetManager>()->CloseUserWidget(InSlotTag, OnCloseFinish);
}

void UBPFunctions_Widget::SwitchGameMenu(UGameMenuSetting* InGameMenuSetting)
{
	if (GetManager<UScreenWidgetManager>())
	{
		GetManager<UScreenWidgetManager>()->SwitchGameMenu(InGameMenuSetting);
	}
}

void UBPFunctions_Widget::SelectMenu(const FGameplayTag InMenuTag)
{
	if (GetManager<UScreenWidgetManager>())
	{
		GetManager<UScreenWidgetManager>()->SelectMenu(InMenuTag);
	}
}

void UBPFunctions_Widget::DeselectMenu(const FGameplayTag InMenuTag)
{
	if (GetManager<UScreenWidgetManager>())
	{
		GetManager<UScreenWidgetManager>()->DeselectMenu(InMenuTag);
	}
}

bool UBPFunctions_Widget::GetMenuContainerInfo(const FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo)
{
	if (GetManager<UScreenWidgetManager>())
	{
		return GetManager<UScreenWidgetManager>()->GetMenuContainerInfo(InMenuTag, OutMenuContainerInfo);
	}
	return false;
}

bool UBPFunctions_Widget::GetMenuParentContainerInfo(const FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo)
{
	if (GetManager<UScreenWidgetManager>())
	{
		return GetManager<UScreenWidgetManager>()->GetMenuParentContainerInfo(InMenuTag, OutMenuContainerInfo);
	}
	return false;
}

bool UBPFunctions_Widget::GetMenuGenerateInfo(const FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo)
{
	if (GetManager<UScreenWidgetManager>())
	{
		return GetManager<UScreenWidgetManager>()->GetMenuGenerateInfo(InMenuTag, OutMenuGenerateInfo);
	}
	return false;
}

bool UBPFunctions_Widget::GetMenuParentGenerateInfo(const FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo)
{
	if (GetManager<UScreenWidgetManager>())
	{
		return GetManager<UScreenWidgetManager>()->GetMenuParentGenerateInfo(InMenuTag, OutMenuGenerateInfo);
	}
	return false;
}

UMenuStyle* UBPFunctions_Widget::GetMenuStyle(const FGameplayTag InMenuTag)
{
	return GetManager<UScreenWidgetManager>()->GetMenuStyle(InMenuTag);
}

UMenuStyle* UBPFunctions_Widget::GetParentMenuStyle(const FGameplayTag InMenuTag)
{
	return GetManager<UScreenWidgetManager>()->GetParentMenuStyle(InMenuTag);
}

TArray<UMenuStyle*> UBPFunctions_Widget::GetAllMenuStyle()
{
	return GetManager<UScreenWidgetManager>()->GetAllMenuStyle();
}

FGameplayTag UBPFunctions_Widget::GetLastActiveMenuTag()
{
	return GetManager<UScreenWidgetManager>()->GetLastActiveMenuTag();
}

FGameplayTag UBPFunctions_Widget::GetCurrentActiveMenuTag()
{
	return GetManager<UScreenWidgetManager>()->GetCurrentActiveMenuTag();
}
