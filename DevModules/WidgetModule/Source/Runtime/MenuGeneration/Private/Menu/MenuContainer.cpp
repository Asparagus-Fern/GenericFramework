// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuContainer.h"

#include "ScreenWidgetManager.h"
#include "Group/CommonButtonGroup.h"
#include "Menu/MenuStyle.h"

UMenuContainer::UMenuContainer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	DesignMenuStyleClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/WidgetModule/Widget/MenuStyle/WBP_Style_Example.WBP_Style_Example_C'"));
#endif
}

void UMenuContainer::ConstructMenuContainer_Implementation(UMenuStyle* MenuStyle, int32 Index)
{
}

void UMenuContainer::NativePreConstruct()
{
	Super::NativePreConstruct();

#if WITH_EDITOR
	if (IsDesignTime())
	{
		for (const auto& DesignMenuStyle : DesignMenuStyles)
		{
			DestructMenuContainer(DesignMenuStyle);
			DesignMenuStyle->MarkAsGarbage();
		}

		DesignMenuStyles.Reset();

		if (IsValid(DesignMenuStyleClass))
		{
			for (int Index = 0; Index < DesignMenuNum; Index++)
			{
				UMenuStyle* NewDesignMenuStyle = CreateWidget<UMenuStyle>(this, DesignMenuStyleClass);
				DesignMenuStyles.Add(NewDesignMenuStyle);
				ConstructMenuContainer(NewDesignMenuStyle, Index);
			}
		}
	}
#endif
}

void UMenuContainer::NativeOnCreate()
{
	Super::NativeOnCreate();

	CommonButtonGroup = NewObject<UCommonButtonGroup>(this, "CommonButtonGroup");
	MenuStyles.Reset();
}

void UMenuContainer::NativeConstructMenuContainer(UMenuStyle* MenuStyle, int32 Index)
{
	if (!IsValid(MenuStyle) || MenuStyles.Contains(MenuStyle))
	{
		DLOG(DLogUI, Error, TEXT("Fail To Construct Menu Container"))
		return;
	}

	MenuStyles.Add(MenuStyle);

	/* 将菜单加入到CommonButtonGroup管理 */
	if (bIsManagedByGroup && IsValid(MenuStyle->ActiveCommonButton))
	{
		CommonButtonGroup->AddWidget(MenuStyle->ActiveCommonButton);
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
		DLOG(DLogUI, Error, TEXT("Fail To Construct Menu Container"))
		return;
	}

	DestructMenuContainer(MenuStyle);

	MenuStyles.Remove(MenuStyle);

	if (bIsManagedByGroup && IsValid(MenuStyle->ActiveCommonButton))
	{
		CommonButtonGroup->RemoveWidget(MenuStyle->ActiveCommonButton);
	}
}

void UMenuContainer::PostConstructMenuContainer_Implementation()
{
}

void UMenuContainer::NativePostConstructMenuContainer()
{
	PostConstructMenuContainer();
}
