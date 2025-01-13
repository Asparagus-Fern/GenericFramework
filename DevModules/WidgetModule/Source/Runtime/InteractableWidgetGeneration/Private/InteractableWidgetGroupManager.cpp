// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/InteractableWidgetGroupManager.h"

#include "Group/CommonButton.h"
#include "Group/CommonButtonGroup.h"
#include "UserWidget/Base/InteractableUserWidgetBase.h"

bool UInteractableWidgetGroupManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UInteractableWidgetGroupManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	UInteractableUserWidgetBase::AddInteractableWidget.AddUObject(this, &UInteractableWidgetGroupManager::AddInteractableWidget);
	UInteractableUserWidgetBase::RemoveInteractableWidget.AddUObject(this, &UInteractableWidgetGroupManager::RemoveInteractableWidget);
}

void UInteractableWidgetGroupManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();

	UInteractableUserWidgetBase::AddInteractableWidget.RemoveAll(this);
	UInteractableUserWidgetBase::RemoveInteractableWidget.RemoveAll(this);
}

bool UInteractableWidgetGroupManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UInteractableWidgetGroupManager::AddInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName)
{
	/* 查找按钮组是否存在，不存在则创建 */
	if (!InteractableWidgetGroups.Contains(GroupName))
	{
		UCommonButtonGroup* NewGroup = NewObject<UCommonButtonGroup>(this);
		InteractableWidgetGroups.FindOrAdd(GroupName, NewGroup);
	}

	/* 添加到按钮组 */
	if (IsValid(InteractableWidget->ActiveCommonButton))
	{
		InteractableWidgetGroups.FindRef(GroupName)->AddWidget(InteractableWidget->ActiveCommonButton);
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnInteractableWidgetAdded, BPDelegate_OnInteractableWidgetAdded, InteractableWidget, GroupName)
	}
}

void UInteractableWidgetGroupManager::RemoveInteractableWidget(UInteractableUserWidgetBase* InteractableWidget, FString GroupName)
{
	/* 查找按钮组并移除指定Widget */
	UCommonButtonGroup* Group = InteractableWidgetGroups.FindRef(GroupName);
	if (IsValid(Group))
	{
		if (IsValid(InteractableWidget->ActiveCommonButton))
		{
			BROADCAST_UNIFIED_DELEGATE(Delegate_OnInteractableWidgetRemoved, BPDelegate_OnInteractableWidgetRemoved, InteractableWidget, GroupName)
			Group->RemoveWidget(InteractableWidget->ActiveCommonButton);
		}

		/* 当该组数量为0时，销毁该按钮组 */
		if (Group->GetButtonCount() == 0)
		{
			InteractableWidgetGroups.Remove(GroupName);
			Group->MarkAsGarbage();
		}
	}
}

void UInteractableWidgetGroupManager::ClearupInteractableWidgetGroup(const FString& GroupName, const bool DeselectAll)
{
	/* 清除一个按钮组 */
	if (InteractableWidgetGroups.Contains(GroupName))
	{
		UCommonButtonGroup* RemoveGroup = InteractableWidgetGroups.FindAndRemoveChecked(GroupName);

		if (DeselectAll)
		{
			RemoveGroup->DeselectAll();
		}

		RemoveGroup->MarkAsGarbage();
	}

	BROADCAST_UNIFIED_DELEGATE(Delegate_OnInteractableWidgetClearup, BPDelegate_OnInteractableWidgetClearup, GroupName)
}

bool UInteractableWidgetGroupManager::FindInteractableWidgetGroup(const FString& GroupName, UCommonButtonGroup*& Group) const
{
	/* 查找一个按钮组 */
	if (InteractableWidgetGroups.Contains(GroupName))
	{
		Group = InteractableWidgetGroups.FindRef(GroupName);
		return true;
	}

	return false;
}
