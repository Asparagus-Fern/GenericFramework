// Fill out your copyright notice in the Description page of Project Settings.


#include "SMenuCollectionHierarchyRow.h"

#include "SlateOptMacros.h"
#include "SMenuCollectionHierarchy.h"
#include "Entity/MenuEntity.h"
#include "Entity/MenuGroupEntity.h"

FMenuCollectionHierarchyRow::FMenuCollectionHierarchyRow(TObjectPtr<UMenuEntityBase> InMenuEntity)
{
	MenuEntity = InMenuEntity;
}

UMenuEntity* FMenuCollectionHierarchyRow::GetMenuEntity() const
{
	return Cast<UMenuEntity>(MenuEntity);
}

UMenuGroupEntity* FMenuCollectionHierarchyRow::GetMenuGroupEntity() const
{
	return Cast<UMenuGroupEntity>(MenuEntity);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMenuCollectionHierarchyRow::Construct(const FArguments& InArgs, const FMenuCollectionHierarchyRowPtr& InRow)
{
	MenuCollectionHierarchyRowPtr = InRow;

	if (MenuCollectionHierarchyRowPtr.IsValid())
	{
		ChildSlot
		[
			SNew(STextBlock)
			.Text(this, &SMenuCollectionHierarchyRow::GetHierarchyRowName)
		];
	}
}

FText SMenuCollectionHierarchyRow::GetHierarchyRowName() const
{
	if (MenuCollectionHierarchyRowPtr.IsValid())
	{
		return FText::FromString(MenuCollectionHierarchyRowPtr->GetMenuEntity()->MenuTag.ToString() + "(" + MenuCollectionHierarchyRowPtr->GetMenuEntity()->MenuMainName.ToString() + ")");
	}
	return FText::FromString("Error Menu Entity");
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
