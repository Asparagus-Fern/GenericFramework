// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Menu/Container/MenuSplineContainer.h"

#include "BPFunctions/BPFunctions_Slate.h"
#include "UserWidget/Menu/MenuStyle.h"
#include "UWidget/Spline2D.h"
#include "UWidget/Spline2DSlot.h"

void UMenuSplineContainer::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	UpdateMenuPositionAtSpline();
}

void UMenuSplineContainer::ConstructMenuContainer_Implementation(UMenuStyle* MenuStyle, int32 Index)
{
	Super::ConstructMenuContainer_Implementation(MenuStyle, Index);

	if (Spline2D)
	{
		Spline2D->AddChildToSpline2D(MenuStyle);
		UpdateMenuPositionAtSpline();
	}
}

void UMenuSplineContainer::DestructMenuContainer_Implementation(UMenuStyle* MenuStyle)
{
	Super::DestructMenuContainer_Implementation(MenuStyle);

	if (Spline2D)
	{
		Spline2D->RemoveChild(MenuStyle);
		UpdateMenuPositionAtSpline();
	}
}

void UMenuSplineContainer::UpdateMenuPositionAtSpline_Implementation()
{
	if (Spline2D)
	{
#if WITH_EDITOR
		TArray<UMenuStyle*> Menus = IsDesignTime() ? DesignMenuStyles : MenuStyles;
#else
		TArray<UMenuStyle*> Menus = MenuStyles;
#endif

		for (int32 Index = 0; Index < Menus.Num(); Index++)
		{
			if (USpline2DSlot* Spline2DSlot = UBPFunctions_Slate::SlotAsSpline2DSlot(Menus[Index]))
			{
				Spline2DSlot->SetValue(((Spline2D->GetSplineInfo().Duration / 2) - ((Menus.Num() - 1) * SpacingAtSpline) / 2) + Index * SpacingAtSpline);
			}
		}
	}
}
