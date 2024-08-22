// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Menu/MenuContainer.h"

#include "ScreenWidgetManager.h"
#include "Group/CommonButtonGroup.h"
#include "UserWidget/Menu/MenuStyle.h"

UMenuContainer::UMenuContainer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CommonButtonGroup = CreateDefaultSubobject<UCommonButtonGroup>("CommonButtonGroup");
}

void UMenuContainer::ConstructMenuContainer_Implementation(UMenuStyle* MenuStyle, int32 Index)
{
}

void UMenuContainer::NativeConstructMenuContainer(UMenuStyle* MenuStyle, int32 Index)
{
	if (!IsValid(MenuStyle) || MenuStyles.Contains(MenuStyle))
	{
		LOG(Debug_UI, Error, TEXT("Fail To Construct Menu Container"))
		return;
	}

	MenuStyles.Add(MenuStyle);

	/* 将菜单加入到CommonButtonGroup管理 */
	if (bIsManagedByGroup && IsValid(MenuStyle->CommonButton))
	{
		CommonButtonGroup->AddWidget(MenuStyle->CommonButton);
	}

	ConstructMenuContainer(MenuStyle, Index);
}

void UMenuContainer::DestructMenuContainer_Implementation(UMenuStyle* MenuStyle)
{
}

void UMenuContainer::NativeDestructMenuContainer(UMenuStyle* MenuStyle)
{
	if (!IsValid(MenuStyle) || !MenuStyles.Contains(MenuStyle))
	{
		LOG(Debug_UI, Error, TEXT("Fail To Construct Menu Container"))
		return;
	}

	DestructMenuContainer(MenuStyle);

	MenuStyles.Remove(MenuStyle);

	if (bIsManagedByGroup && IsValid(MenuStyle->CommonButton))
	{
		CommonButtonGroup->RemoveWidget(MenuStyle->CommonButton);
	}
}

void UMenuContainer::PostConstructMenuContainer_Implementation()
{
}

void UMenuContainer::NativePostConstructMenuContainer()
{
	PostConstructMenuContainer();
}
