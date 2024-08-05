#include "ScreenWidgetType.h"

#include "ScreenWidgetManager.h"
#include "Group/CommonButtonGroup.h"
#include "Groups/CommonButtonGroupBase.h"
#include "Manager/ManagerGlobal.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "UserWidget/Menu/MenuStyle.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_UMG, "UMG");
UE_DEFINE_GAMEPLAY_TAG(TAG_Menu, "Menu");

FSimpleMulticastDelegate FScreenWidgetDelegates::OnHUDCreated;
FSimpleMulticastDelegate FScreenWidgetDelegates::OnMenuCleanup;
FSimpleMulticastDelegate FScreenWidgetDelegates::OnMenuGenerated;
FScreenWidgetDelegates::FUserWidgetDelegate FScreenWidgetDelegates::OnWidgetOpen;
FScreenWidgetDelegates::FUserWidgetDelegate FScreenWidgetDelegates::OnWidgetClose;
FScreenWidgetDelegates::FMenuDelegate FScreenWidgetDelegates::OnMenuClicked;
FScreenWidgetDelegates::FMenuSelectionDelegate FScreenWidgetDelegates::OnMenuSelectionChanged;
FScreenWidgetDelegates::FWidgetAnimationDelegate FScreenWidgetDelegates::OnWidgetAnimationFinish;

UUserWidgetBase* FWidgetContainer::GetWidget() const
{
	if (bInstance)
	{
		if (IsValid(Widget))
		{
			return Widget;
		}
	}
	else
	{
		if (WidgetClass)
		{
			return CreateWidget<UUserWidgetBase>(GetManager<UScreenWidgetManager>()->GetWorld(), WidgetClass);
		}
	}

	return nullptr;
}

bool FCommonButtonEventModify::CanModify(bool bSelected)
{
	const FGameplayTag LastActiveMenuTag = GetManager<UScreenWidgetManager>()->GetLastActiveMenuTag();
	const FGameplayTag CurrentActiveMenuTag = GetManager<UScreenWidgetManager>()->GetCurrentActiveMenuTag();
	const FGameplayTag CompareMenuTag = bSelected ? (LastActiveMenuTag.IsValid() ? LastActiveMenuTag : CurrentActiveMenuTag) : CurrentActiveMenuTag;

	if (!CompareMenuTag.IsValid())
	{
		return false;
	}

	if (bMatch)
	{
		for (const auto& MenuTag : MenuTags)
		{
			if (CompareMenuTag.MatchesTag(MenuTag))
			{
				return true;
			}
		}
	}
	else
	{
		return MenuTags.Contains(CompareMenuTag);
	}

	return false;
}

FMenuInfo::FMenuInfo()
{
}

FMenuInfo::FMenuInfo(const FGameplayTag InMenuTag)
	: MenuTag(InMenuTag)
{
}

FMenuContainerInfo::FMenuContainerInfo()
{
}

FMenuContainerInfo::FMenuContainerInfo(const FGameplayTag InContainerTag)
	: ContainerTag(InContainerTag)
{
}

FMenuGenerateInfo::FMenuGenerateInfo()
{
}

FMenuGenerateInfo::FMenuGenerateInfo(UCommonButtonGroup* InCommonButtonGroup, const FMenuContainerInfo& InMenuContainerInfo)
	: CommonButtonGroup(InCommonButtonGroup),
	  MenuContainerInfo(InMenuContainerInfo)
{
}

bool FMenuGenerateInfo::HasMenuInfo(const FGameplayTag InMenuTag)
{
	for (const auto& MenuStyle : MenuStyles)
	{
		if (MenuStyle->GetMenuInfo() == InMenuTag)
		{
			return true;
		}
	}

	return false;
}

void FMenuGenerateInfo::SelectMenu(const FGameplayTag InMenuTag)
{
	if (IsValid(CommonButtonGroup) && HasMenuInfo(InMenuTag))
	{
		for (int32 Index = 0; Index != MenuStyles.Num(); ++Index)
		{
			if (MenuStyles[Index]->GetMenuInfo() == InMenuTag)
			{
				CommonButtonGroup->SelectButtonAtIndex(Index);
			}
		}
	}
}

void FMenuGenerateInfo::DeselectMenu(const FGameplayTag InMenuTag)
{
	if (IsValid(CommonButtonGroup) && HasMenuInfo(InMenuTag))
	{
		CommonButtonGroup->DeselectAll();
	}
}

UMenuStyle* FMenuGenerateInfo::GetMenuStyle(const FGameplayTag InMenuTag)
{
	if (HasMenuInfo(InMenuTag))
	{
		for (const auto& MenuStyle : MenuStyles)
		{
			if (MenuStyle->GetMenuInfo() == InMenuTag)
			{
				return MenuStyle;
			}
		}
	}

	return nullptr;
}
