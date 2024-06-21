#include "ScreenWidgetType.h"

#include "Groups/CommonButtonGroupBase.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_HUD, "HUD");
UE_DEFINE_GAMEPLAY_TAG(TAG_Menu, "Menu");

FSimpleMulticastDelegate FScreenWidgetDelegates::OnHUDCreated;
FSimpleMulticastDelegate FScreenWidgetDelegates::OnMenuCleanup;
FSimpleMulticastDelegate FScreenWidgetDelegates::OnMenuGenerated;
FScreenWidgetDelegates::FUserWidgetDelegate FScreenWidgetDelegates::OnWidgetOpen;
FScreenWidgetDelegates::FUserWidgetDelegate FScreenWidgetDelegates::OnWidgetClose;
FScreenWidgetDelegates::FMenuDelegate FScreenWidgetDelegates::OnMenuClicked;
FScreenWidgetDelegates::FMenuSelectionDelegate FScreenWidgetDelegates::OnMenuSelectionChanged;

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

FMenuGenerateInfo::FMenuGenerateInfo(UCommonButtonGroup* InCommonButtonGroup, FMenuContainerInfo InMenuContainerInfo)
	: CommonButtonGroup(InCommonButtonGroup),
	  MenuContainerInfo(InMenuContainerInfo)
{
}
