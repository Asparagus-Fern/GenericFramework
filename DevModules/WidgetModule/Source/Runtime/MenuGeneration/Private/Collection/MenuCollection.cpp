// Fill out your copyright notice in the Description page of Project Settings.


#include "Collection/MenuCollection.h"

#include "GameplayTagsManager.h"
#include "MenuType.h"
#include "BPFunctions/BPFunctions_GameplayTag.h"
#include "Debug/DebugType.h"
#include "Entity/MenuEntity.h"
#include "Entity/MenuGroupEntity.h"

UMenuCollection::UMenuCollection(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MenuClass = UMenuEntity::StaticClass();
	MenuGroupClass = UMenuGroupEntity::StaticClass();
}

void UMenuCollection::NativeOnActived()
{
	IStateInterface::NativeOnActived();

	if (UMenuEntityBase* RootEntity = GetRootMenuEntity())
	{
		RootEntity->NativeOnActived();
	}
}

void UMenuCollection::NativeOnInactived()
{
	IStateInterface::NativeOnInactived();

	if (UMenuEntityBase* RootEntity = GetRootMenuEntity())
	{
		RootEntity->NativeOnInactived();
	}
}

bool UMenuCollection::GetIsActived() const
{
	return IStateInterface::GetIsActived();
}

void UMenuCollection::SetIsActived(const bool InActived)
{
	IStateInterface::SetIsActived(InActived);
}

void UMenuCollection::ReGenerateMenu()
{
	ReGenerateMenu(MenuTagTable);
}

void UMenuCollection::ReGenerateMenu(UDataTable* InMenuTagTable)
{
	Modify();

	ClearupMenu();
	GenerateMenu(InMenuTagTable);
}

void UMenuCollection::GenerateMenu()
{
	GenerateMenu(MenuTagTable);
}

void UMenuCollection::GenerateMenu(UDataTable* InMenuTagTable)
{
	if (!IsValid(MenuTagTable))
	{
		DNOTIFY(TEXT("MenuTagTable is NULL"))
		return;
	}

	if (!MenuTagTable->RowStruct->IsChildOf(FGameplayTagTableRow::StaticStruct()))
	{
		DNOTIFY(TEXT("MenuTagTable is not a GameplayTag Table"))
		return;
	}

	if (!MenuClass || !MenuGroupClass)
	{
		DNOTIFY(TEXT("MenuClass/MenuGroupClass is NULL"))
		return;
	}

	Modify();

	GameplayTagContainer = FGameplayTagContainer();

	FGameplayTag RootMenuTag = FGameplayTag::RequestGameplayTag("UI.Menu");
	GameplayTagContainer.AddTag(RootMenuTag);

	/* Get The Owner Tag */
	MenuTagTable->ForeachRow<FGameplayTagTableRow>
	("", [this, RootMenuTag](FName Key, const FGameplayTagTableRow& Value)
	 {
		 const FGameplayTag MenuTag = FGameplayTag::RequestGameplayTag(Value.Tag);
		 if (UBPFunctions_GameplayTag::GetDirectGameplayTagParent(MenuTag) == RootMenuTag)
		 {
			 OwnerTag = MenuTag;
		 }
	 }
	);

	if (!OwnerTag.IsValid())
	{
		DNOTIFY(TEXT("GameplayTag Table Must Have a TagRow That its Parent GameplayTag Equal With %s"), *RootMenuTag.ToString())
		return;
	}

	/* Fill Menu Tag In GameplayTagContainer */
	MenuTagTable->ForeachRow<FGameplayTagTableRow>
	("", [this, RootMenuTag](FName Key, const FGameplayTagTableRow& Value)
	 {
		 const FGameplayTag MenuTag = FGameplayTag::RequestGameplayTag(Value.Tag);

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
		 if (IsContainMenuTag(MenuTag))
		 {
			 DLOG(DLogUI, Warning, TEXT("MenuTag : %s Is Already Generated"), *MenuTag.ToString())
			 return;
		 }

		 /* Add In GameplayTagContainer And Make MenuEntity */
		 GameplayTagContainer.AddTag(MenuTag);

		 UMenuEntityBase* NewMenu = nullptr;

		 if (UBPFunctions_GameplayTag::GetDirectGameplayTagChildren(MenuTag).IsEmpty())
		 {
			 NewMenu = NewObject<UMenuEntity>(this, MenuClass);
		 }
		 else
		 {
			 NewMenu = NewObject<UMenuGroupEntity>(this, MenuGroupClass);
		 }

		 NewMenu->MenuTag = MenuTag;
		 NewMenu->MenuMainName = FText::FromString(Value.DevComment);

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

bool UMenuCollection::IsContainMenuTag(const FGameplayTag InMenuTag)
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

bool UMenuCollection::IsContainMenu(const UMenuEntityBase* InMenuEntity)
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

UMenuEntityBase* UMenuCollection::GetRootMenuEntity()
{
	return GetMenuEntity(OwnerTag);
}

UMenuEntityBase* UMenuCollection::GetMenuEntity(FGameplayTag InMenuTag)
{
	if (!InMenuTag.IsValid())
	{
		DLOG(DLogUI, Error, TEXT("InMenuTag Is NULL"))
		return nullptr;
	}

	for (const auto& MenuEntity : MenuEntities)
	{
		if (MenuEntity->MenuTag == InMenuTag)
		{
			return MenuEntity;
		}
	}
	return nullptr;
}

TArray<UMenuEntityBase*> UMenuCollection::GetMenuEntities(const TArray<FGameplayTag>& InMenuTags)
{
	TArray<UMenuEntityBase*> Result;
	for (const auto& MenuEntity : MenuEntities)
	{
		if (InMenuTags.Contains(MenuEntity->MenuTag))
		{
			Result.Add(MenuEntity);
		}
	}
	return Result;
}

UMenuEntityBase* UMenuCollection::GetParentMenuEntity(FGameplayTag InMenuTag)
{
	return GetMenuEntity(UBPFunctions_GameplayTag::GetDirectGameplayTagParent(InMenuTag));
}

TArray<UMenuEntityBase*> UMenuCollection::GetChildMenuEntities(FGameplayTag InMenuTag)
{
	return GetMenuEntities(UBPFunctions_GameplayTag::GetGameplayTagChildren(InMenuTag).GetGameplayTagArray());
}

TArray<UMenuEntityBase*> UMenuCollection::GetDirectChildMenuEntities(FGameplayTag InMenuTag)
{
	return GetMenuEntities(UBPFunctions_GameplayTag::GetDirectGameplayTagChildren(InMenuTag).GetGameplayTagArray());
}

void UMenuCollection::ActiveMenus(UMenuEntityBase* InEntities)
{
}

void UMenuCollection::ActiveMenu(UMenuEntityBase* InEntity)
{
}
