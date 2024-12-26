// Fill out your copyright notice in the Description page of Project Settings.


#include "ShortcutWidgetManager.h"

#include "ScreenWidgetManager.h"
#include "ScreenWidgetManagerSetting.h"
#include "ScreenWidgetType.h"
#include "BPFunctions/BPFunctions_Object.h"
#include "Kismet/GameplayStatics.h"
#include "Shortcut/ShortcutWidgetHandle.h"
#include "UserWidget/Base/UserWidgetBase.h"

bool UShortcutWidgetManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UShortcutWidgetManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UScreenWidgetManager::OnWidgetOpen.AddUObject(this, &UShortcutWidgetManager::OnWidgetOpen);
	UScreenWidgetManager::OnWidgetClose.AddUObject(this, &UShortcutWidgetManager::OnWidgetClose);
}

void UShortcutWidgetManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UScreenWidgetManager::OnWidgetOpen.RemoveAll(this);
	UScreenWidgetManager::OnWidgetClose.RemoveAll(this);
}

bool UShortcutWidgetManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UShortcutWidgetManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);
}

void UShortcutWidgetManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	RegisterShortcutWidgetHandles();
}

void UShortcutWidgetManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);
	UnRegisterShortcutWidgetHandles();
}

void UShortcutWidgetManager::OnWidgetOpen(UUserWidgetBase* InWidget)
{
	if (UShortcutWidgetHandle* ShortcutWidgetHandle = GetShortcutWidgetHandle(InWidget))
	{
		ShortcutWidgetHandle->Link(InWidget);
	}
}

void UShortcutWidgetManager::OnWidgetClose(UUserWidgetBase* InWidget)
{
	if (UShortcutWidgetHandle* ShortcutWidgetHandle = GetShortcutWidgetHandle(InWidget))
	{
		ShortcutWidgetHandle->UnLink();
	}
}

void UShortcutWidgetManager::RegisterShortcutWidgetHandles()
{
	if (!UScreenWidgetManagerSetting::Get()->ShortcutWidgetTable.IsNull())
	{
		UDataTable* DataTable = UBPFunctions_Object::LoadObject<UDataTable>(UScreenWidgetManagerSetting::Get()->ShortcutWidgetTable);
		if (IsValid(DataTable))
		{
			if (!DataTable->RowStruct->IsChildOf(FShortcutWidgetTableRow::StaticStruct()))
			{
				return;
			}

			ShortcutWidgetTable = DataTable;

			ShortcutWidgetTable->ForeachRow<FShortcutWidgetTableRow>
			("", [this](FName Key, const FShortcutWidgetTableRow& Value)
			 {
				 if (!Value.ShortcutWidgetHandleClass || !Value.WidgetClass || !IsValid(Value.InputAction))
				 {
					 return;
				 }

				 /* PlayerIndex不存在 */
				 if (!UGameplayStatics::GetPlayerController(this, Value.PlayerIndex))
				 {
					 return;
				 }

				 /* 相同WidgetClass映射了多个InputAction */
				 if (IsValid(GetShortcutWidgetHandle(Value.WidgetClass)))
				 {
					 return;
				 }

				 UShortcutWidgetHandle* ShortcutWidgetHandle = NewObject<UShortcutWidgetHandle>(this, Value.ShortcutWidgetHandleClass);
				 ShortcutWidgetHandle->ShortcutWidgetTableRow = Value;
				 ShortcutWidgetHandles.Add(ShortcutWidgetHandle);

				 ShortcutWidgetHandle->NativeOnCreate();
			 }
			);
		}
	}
}

void UShortcutWidgetManager::UnRegisterShortcutWidgetHandles()
{
	for (const auto& ShortcutWidgetHandle : ShortcutWidgetHandles)
	{
		ShortcutWidgetHandle->NativeOnDestroy();
	}
}

UShortcutWidgetHandle* UShortcutWidgetManager::GetShortcutWidgetHandle(const UUserWidgetBase* InWidget)
{
	for (const auto& ShortcutWidgetHandle : ShortcutWidgetHandles)
	{
		if (ShortcutWidgetHandle->Equal(InWidget))
		{
			return ShortcutWidgetHandle;
		}
	}

	return nullptr;
}

UShortcutWidgetHandle* UShortcutWidgetManager::GetShortcutWidgetHandle(const TSubclassOf<UUserWidgetBase> InWidgetClass)
{
	for (const auto& ShortcutWidgetHandle : ShortcutWidgetHandles)
	{
		if (ShortcutWidgetHandle->Equal(InWidgetClass))
		{
			return ShortcutWidgetHandle;
		}
	}

	return nullptr;
}
