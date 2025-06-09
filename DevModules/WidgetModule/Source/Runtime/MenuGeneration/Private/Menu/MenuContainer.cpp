// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Menu/MenuContainer.h"

#include "Components/PanelWidget.h"
#include "Entity/MenuGroupEntity.h"
#include "Menu/MenuStyle.h"

UMenuContainer::UMenuContainer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	DesignMenuStyleClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/WidgetModule/Widget/MenuStyle/WBP_Style_Example.WBP_Style_Example_C'"));
#endif
}

void UMenuContainer::NativePreConstruct()
{
	Super::NativePreConstruct();

#if WITH_EDITOR
	if (IsDesignTime())
	{
		if (IsValid(Content))
		{
			Content->ClearChildren();
		}

		for (const auto& DesignMenuStyle : DesignMenuStyles)
		{
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

void UMenuContainer::ConstructMenuContainer_Implementation(UMenuStyle* MenuStyle, int32 Index)
{
}

void UMenuContainer::NativeConstructMenuContainer(UMenuStyle* MenuStyle, int32 Index)
{
	if (!IsValid(MenuStyle) || MenuStyles.Contains(MenuStyle))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Fail To Construct Menu Container"))
		return;
	}

	MenuStyles.Add(MenuStyle);
	ConstructMenuContainer(MenuStyle, Index);
}

void UMenuContainer::PostConstructMenuContainer_Implementation()
{
}

void UMenuContainer::NativePostConstructMenuContainer()
{
	PostConstructMenuContainer();
}

UMenuGroupEntity* UMenuContainer::GetMenuGroupEntity()
{
	return GetWidgetEntity<UMenuGroupEntity>();
}
