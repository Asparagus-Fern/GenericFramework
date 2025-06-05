// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Collection/MenuCollection.h"

#include "GameHUDManager.h"
#include "GameplayTagsManager.h"
#include "MenuType.h"
#include "WidgetEntityManager.h"
#include "BPFunctions/BPFunctions_GameplayTag.h"
#include "Debug/DebugType.h"
#include "Entity/MenuEntity.h"
#include "Entity/MenuGroupEntity.h"
#include "Manager/ManagerStatics.h"

UMenuCollection::UMenuCollection(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MenuClass = UMenuEntity::StaticClass();
	MenuGroupClass = UMenuGroupEntity::StaticClass();
}

void UMenuCollection::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();

	UGameHUDManager::Delegate_PostHUDCreated.AddUObject(this, &UMenuCollection::PostHUDCreated);
}

void UMenuCollection::NativeOnActived()
{
	IStateInterface::NativeOnActived();

	for (auto& MenuEntity : MenuEntities)
	{
		MenuEntity->Collection = this;
	}
}

void UMenuCollection::NativeOnInactived()
{
	IStateInterface::NativeOnInactived();

	if (UMenuEntityBase* RootEntity = GetRootMenuEntity())
	{
		RootEntity->NativeOnInactived();

		if (UWidgetEntityManager* WidgetEntityManager = GetManager<UWidgetEntityManager>())
		{
			WidgetEntityManager->UnRegisterWidgetEntity(RootEntity);
		}
	}
}

void UMenuCollection::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();
}

bool UMenuCollection::GetIsActived() const
{
	return IStateInterface::GetIsActived();
}

void UMenuCollection::SetIsActived(const bool InActived)
{
	IStateInterface::SetIsActived(InActived);
}

void UMenuCollection::PostHUDCreated()
{
	UGameHUDManager::Delegate_PostHUDCreated.RemoveAll(this);

	if (GetIsActived())
	{
		if (UMenuEntityBase* RootEntity = GetRootMenuEntity())
		{
			if (UWidgetEntityManager* WidgetEntityManager = GetManager<UWidgetEntityManager>())
			{
				WidgetEntityManager->RegisterWidgetEntity(RootEntity);
			}

			RootEntity->NativeOnActived();
		}
	}
}

#if WITH_EDITOR

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
		GenericNOTIFY(TEXT("MenuTagTable is NULL"))
		return;
	}

	if (!MenuTagTable->RowStruct->IsChildOf(FGameplayTagTableRow::StaticStruct()))
	{
		GenericNOTIFY(TEXT("MenuTagTable is not a GameplayTag Table"))
		return;
	}

	if (!MenuClass || !MenuGroupClass)
	{
		GenericNOTIFY(TEXT("MenuClass/MenuGroupClass is NULL"))
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
		GenericNOTIFY(TEXT("GameplayTag Table Must Have a TagRow That its Parent GameplayTag Equal With %s"), *RootMenuTag.ToString())
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
			 GenericLOG(UILog, Error, TEXT("%s Is Not Under %s"), *MenuTag.ToString(), *RootMenuTag.ToString())
			 return;
		 }

		 /* Skip The RootMenuTag */
		 if (MenuTag == RootMenuTag)
		 {
			 GenericLOG(UILog, Warning, TEXT("%s Is Disable To Generated"), *RootMenuTag.ToString())
			 return;
		 }

		 /* Skip The Tag Already In GameplayTagContainer */
		 if (IsContainMenuTag(MenuTag))
		 {
			 GenericLOG(UILog, Warning, TEXT("MenuTag : %s Is Already Generated"), *MenuTag.ToString())
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
		 NewMenu->Initialize();

		 MenuEntities.Add(NewMenu);
	 }
	);

	GenericNOTIFY(TEXT("Generate Menu Finish"))
}

void UMenuCollection::ClearupMenu()
{
	OwnerTag = FGameplayTag::EmptyTag;
	MenuEntities.Reset();
	GameplayTagContainer.Reset();
}

#endif

bool UMenuCollection::IsContainMenuTag(const FGameplayTag InMenuTag)
{
	if (!InMenuTag.IsValid())
	{
		GenericLOG(UILog, Error, TEXT("InMenuTag Is NULL"))
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
		GenericLOG(UILog, Error, TEXT("InMenuEntity Is NULL"))
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
		GenericLOG(UILog, Error, TEXT("InMenuTag Is NULL"))
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

void UMenuCollection::ActiveMenu(UMenuEntityBase* InEntity)
{
}
