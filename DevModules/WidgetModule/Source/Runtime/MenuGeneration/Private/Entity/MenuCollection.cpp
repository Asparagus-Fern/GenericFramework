// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuCollection.h"

#include "GameplayTagsManager.h"
#include "MenuType.h"
#include "BPFunctions/BPFunctions_GameplayTag.h"
#include "Debug/DebugType.h"
#include "Entity/MenuEntity.h"

void UMenuCollection::GenerateMenu(UDataTable* InMenuTagTable)
{
	if (!IsValid(MenuTagTable))
	{
		DNOTIFY(TEXT("MenuTagTable is NULL"))
		return;
	}

	if (!MenuTagTable->RowStruct->IsChildOf(FMenuTagTableRow::StaticStruct()))
	{
		DNOTIFY(TEXT("MenuTagTable is not a GameplayTag Table"))
		return;
	}

	Modify();

	GameplayTagContainer = FGameplayTagContainer();

	FGameplayTag RootMenuTag = FGameplayTag::RequestGameplayTag("UI.Menu");
	GameplayTagContainer.AddTag(RootMenuTag);

	/* Get The Owner Tag */
	MenuTagTable->ForeachRow<FMenuTagTableRow>
	("", [this, RootMenuTag](FName Key, const FMenuTagTableRow& Value)
	 {
		 const FGameplayTag MenuTag = FGameplayTag::RequestGameplayTag(Value.MenuTag);
		 if (UBPFunctions_GameplayTag::GetDirectGameplayTagParent(MenuTag) == RootMenuTag)
		 {
			 OwnerTag = FGameplayTag::EmptyTag;
		 }
	 }
	);

	if (!OwnerTag.IsValid())
	{
		DNOTIFY(TEXT("GameplayTag Table Must Have a TagRow That its Parent GameplayTag Equal With %s"), *RootMenuTag.ToString())
		return;
	}

	/* Fill Menu Tag In GameplayTagContainer */
	MenuTagTable->ForeachRow<FMenuTagTableRow>
	("", [this, RootMenuTag](FName Key, const FMenuTagTableRow& Value)
	 {
		 const FGameplayTag MenuTag = FGameplayTag::RequestGameplayTag(Value.MenuTag);

		 /* Skip The Tag Not Under The RootMenuTag */
		 if (!MenuTag.GetGameplayTagParents().HasTag(RootMenuTag))
		 {
			 DLOG(DLogUI, Error, TEXT("%s Is Not Under %s"), *MenuTag.ToString(), *RootMenuTag.ToString())
			 return;
		 }

		 /* Skip The RootMenuTag */
		 if (MenuTag == RootMenuTag)
		 {
			 DLOG(DLogUI, Warning, TEXT("%s Is Disable To Generated"), *RootMenuTag.ToString())
			 return;
		 }

		 /* Skip The Tag Already In GameplayTagContainer */
		 if (ContainerMenu(MenuTag))
		 {
			 DLOG(DLogUI, Warning, TEXT("MenuTag : %s Is Already Generated"), *MenuTag.ToString())
			 return;
		 }

		 /* Add In GameplayTagContainer And Make MenuEntity */
		 GameplayTagContainer.AddTag(MenuTag);

		 UMenuEntity* NewMenu = NewObject<UMenuEntity>(this);
		 NewMenu->MenuMainName = Value.MenuMainName;
		 NewMenu->MenuSubName = Value.MenuSubName;
		 NewMenu->MenuToolTip = Value.MenuToolTip;
		 NewMenu->MenuIcon = Value.MenuIcon;

		 MenuEntities.Add(NewMenu);
	 }
	);

	DNOTIFY(TEXT("Generate Menu Finish"))
}

void UMenuCollection::ClearupMenu()
{
	OwnerTag = FGameplayTag::EmptyTag;
	MenuEntities.Reset();
	GameplayTagContainer.Reset();
}

bool UMenuCollection::ContainerMenu(const FGameplayTag InMenuTag)
{
	if (!InMenuTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("InMenuTag Is NULL"))
		return false;
	}

	for (const auto& MenuEntity : MenuEntities)
	{
		if (MenuEntity->MenuTag == InMenuTag)
		{
			return true;
		}
	}
	return false;
}

bool UMenuCollection::ContainerMenu(const UMenuEntity* InMenuEntity)
{
	if (!IsValid(InMenuEntity))
	{
		DLOG(DLogUI, Error, TEXT("InMenuEntity Is NULL"))
		return false;
	}

	for (const auto& MenuEntity : MenuEntities)
	{
		if (MenuEntity == InMenuEntity)
		{
			return true;
		}
	}
	return false;
}
