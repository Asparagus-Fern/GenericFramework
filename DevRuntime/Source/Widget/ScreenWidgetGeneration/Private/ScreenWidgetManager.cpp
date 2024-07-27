// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidgetManager.h"

#include "Animation/WidgetAnimationEvent.h"
#include "Blueprint/WidgetTree.h"
#include "BPFunctions/BPFunctions_Widget.h"
#include "DataAsset/GameMenuSetting.h"
#include "Event/CommonButtonEvent.h"
#include "Group/CommonButtonGroup.h"
#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"
#include "StaticFunctions/StaticFunctions_Object.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "UserWidget/HUD/GameHUD.h"
#include "UserWidget/Menu/MenuContainer.h"
#include "UserWidget/Menu/MenuStyle.h"
#include "Widget/TagNameSlot.h"

#define LOCTEXT_NAMESPACE "UScreenWidgetManager"

void UScreenWidgetManager::NativeOnActived()
{
	Super::NativeOnActived();
	CreateGameHUD();
}

void UScreenWidgetManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	for (const auto& Slot : Slots)
	{
		Slot.Value->ClearChildren();
	}

	Slots.Reset();
	SlotWidgets.Reset();
	GameMenu = nullptr;
	MenuGenerateInfos.Reset();
	GameHUD.Reset();

	CurrentActiveMenuTag = FGameplayTag::EmptyTag;
	LastActiveMenuTag = FGameplayTag::EmptyTag;

	MenuSelectionChangedHandle.Reset();
	TargetMenuSelection.Reset();
	UpdateMenuSelectionHandle.Invalidate();
	TargetMenuSelectionIndex = 0;

	FScreenWidgetDelegates::OnMenuSelectionChanged.RemoveAll(this);
}

FText UScreenWidgetManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Screen Widget Manager");
}

void UScreenWidgetManager::RegisterSlot(UTagNameSlot* InSlot)
{
	if (!IsValid(InSlot) || !InSlot->SlotTag.IsValid() || Slots.Contains(InSlot->SlotTag))
	{
		return;
	}

	Slots.Add(InSlot->SlotTag, InSlot);
}

void UScreenWidgetManager::UnRegisterSlot(const UTagNameSlot* InSlot)
{
	if (!IsValid(InSlot) || !InSlot->SlotTag.IsValid() || !Slots.Contains(InSlot->SlotTag))
	{
		return;
	}

	if (SlotWidgets.Contains(InSlot->SlotTag))
	{
		SlotWidgets.FindRef(InSlot->SlotTag)->NativeOnInactived();
		SlotWidgets.Remove(InSlot->SlotTag);
	}

	Slots.Remove(InSlot->SlotTag);
}

UTagNameSlot* UScreenWidgetManager::GetSlot(const FGameplayTag InSlotTag) const
{
	if (!InSlotTag.IsValid())
	{
		DEBUG(Debug_UI, Error, TEXT("InSlotTag Is NULL"))
		return nullptr;
	}

	if (!Slots.Contains(InSlotTag))
	{
		DEBUG(Debug_UI, Error, TEXT("Slots Is Not Contain InSlotTag"))
		return nullptr;
	}

	return Slots.FindRef(InSlotTag);
}

UUserWidgetBase* UScreenWidgetManager::GetSlotWidget(const FGameplayTag InSlotTag) const
{
	if (!InSlotTag.IsValid())
	{
		DEBUG(Debug_UI, Error, TEXT("InSlotTag Is NULL"))
		return nullptr;
	}

	if (!SlotWidgets.Contains(InSlotTag))
	{
		DEBUG(Debug_UI, Log, TEXT("SlotWidgets Is Not Contains InSlotTag"))
		return nullptr;
	}

	return SlotWidgets.FindRef(InSlotTag);
}

UUserWidgetBase* UScreenWidgetManager::GetSlotUserWidgetByClass(FGameplayTag InSlotTag, TSubclassOf<UUserWidgetBase> InClass) const
{
	ensure(InClass);
	return Cast<UUserWidgetBase>(GetSlotWidget(InSlotTag));
}

TArray<UGameHUD*> UScreenWidgetManager::GetGameHUD()
{
	return GameHUD;
}

TArray<UGameHUD*> UScreenWidgetManager::GetGameHUDByTag(const FGameplayTag InTag)
{
	TArray<UGameHUD*> Result;
	for (auto& HUD : GameHUD)
	{
		if (HUD->SelfTag == InTag)
		{
			Result.Add(HUD);
		}
	}
	return Result;
}

void UScreenWidgetManager::SetGameHUDVisibility(const bool IsVisisble)
{
	for (const auto& HUD : GameHUD)
	{
		HUD->PlayAnimationEvent(IsVisisble);
	}
}

void UScreenWidgetManager::CreateGameHUD()
{
	for (const auto GameHUDClass : GameHUDClasses)
	{
		if (GameHUDClass.IsNull())
			continue;

		TSubclassOf<UGameHUD> LoadHUDClass = FStaticFunctions_Object::LoadClass<UGameHUD>(GameHUDClass);
		UGameHUD* NewHUD = CreateWidget<UGameHUD>(GetWorld(), LoadHUDClass);
		GameHUD.Add(NewHUD);
		NewHUD->AddToViewport(NewHUD->GetViewportZOrder());
	}

	FScreenWidgetDelegates::OnHUDCreated.Broadcast();
}

UUserWidgetBase* UScreenWidgetManager::CreateUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass)
{
	UUserWidgetBase* NewWidget = CreateWidget<UUserWidgetBase>(GetWorld(), InWidgetClass);
	NewWidget->NativeOnCreate();
	return NewWidget;
}

UUserWidgetBase* UScreenWidgetManager::OpenUserWidget(TSubclassOf<UUserWidgetBase> InWidgetClass, FSimpleMulticastDelegate OnFinish)
{
	UUserWidgetBase* NewWidget = CreateUserWidget(InWidgetClass);
	OpenUserWidget(NewWidget, OnFinish);
	return NewWidget;
}

void UScreenWidgetManager::OpenUserWidget(TArray<UUserWidgetBase*> InWidgets)
{
	for (const auto& InWidget : InWidgets)
	{
		OpenUserWidget(InWidget);
	}
}

void UScreenWidgetManager::OpenUserWidget(UUserWidgetBase* InWidget, FSimpleMulticastDelegate OnFinish)
{
	if (!IsValid(InWidget))
	{
		DEBUG(Debug_UI, Warning, TEXT("Can't Open Null UserWidget"))
		return;
	}

	if (!InWidget->SlotTag.IsValid())
	{
		DEBUG(Debug_UI, Warning, TEXT("InWidget SlotTag is NULL"))
		return;
	}

	const FGameplayTag SlotTag = InWidget->SlotTag;
	UTagNameSlot* Slot = GetSlot(SlotTag);
	if (IsValid(Slot))
	{
		/* 如果是在同一个Slot */
		const UUserWidgetBase* OldWidget = GetSlotWidget(SlotTag);
		if (IsValid(OldWidget))
		{
			CloseUserWidget(OldWidget->SlotTag);
		}

		SlotWidgets.Add(Slot->SlotTag, InWidget);
		Slot->SetContent(InWidget);
		ActiveWidget(InWidget, OnFinish);
	}
}

void UScreenWidgetManager::CloseUserWidget(const UUserWidgetBase* InWidget, const FSimpleMulticastDelegate& OnFinish)
{
	if (!IsValid(InWidget))
	{
		DEBUG(Debug_UI, Error, TEXT("InWidget Is NULL"))
		return;
	}

	CloseUserWidget(InWidget->SlotTag, OnFinish);
}

void UScreenWidgetManager::CloseUserWidget(TArray<UUserWidgetBase*> InWidgets)
{
	for (const auto& InWidget : InWidgets)
	{
		GetManager<UScreenWidgetManager>()->CloseUserWidget(InWidget);
	}
}

void UScreenWidgetManager::CloseUserWidget(const FGameplayTag InSlotTag, FSimpleMulticastDelegate OnFinish)
{
	UTagNameSlot* Slot = GetSlot(InSlotTag);
	if (IsValid(Slot))
	{
		UUserWidgetBase* RemoveWidget = GetSlotWidget(InSlotTag);
		if (IsValid(RemoveWidget))
		{
			FSimpleMulticastDelegate OnHandleFinish;
			OnHandleFinish.AddLambda([this, OnFinish]()
				{
					OnFinish.Broadcast();
				}
			);

			InactiveWidget(RemoveWidget, OnHandleFinish);
			Slot->RemoveChild(RemoveWidget);
			SlotWidgets.Remove(RemoveWidget->SlotTag);
		}
	}
}

TArray<FProcedureInterfaceHandle> UScreenWidgetManager::GetProcedureInterfaceHandles(UUserWidget* InWidget, bool TargetActiveState)
{
	TArray<FProcedureInterfaceHandle> ProcedureInterfaceHandles;
	TArray<IProcedureInterface*> ProcedureInterfaces = GetProcedureInterfaceWidgets(InWidget);
	for (const auto& ProcedureInterface : ProcedureInterfaces)
	{
		ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(ProcedureInterface, TargetActiveState));
	}

	return ProcedureInterfaceHandles;
}

TArray<IProcedureInterface*> UScreenWidgetManager::GetProcedureInterfaceWidgets(UUserWidget* InWidget)
{
	TArray<IProcedureInterface*> ProcedureInterfaces;

	if (InWidget->GetClass()->ImplementsInterface(UProcedureInterface::StaticClass()))
	{
		ProcedureInterfaces.Add(Cast<IProcedureInterface>(InWidget));
	}

	/* 遍历所有使用了IProcedureInterface接口的Widget，并激活 */
	InWidget->WidgetTree->ForEachWidget([&ProcedureInterfaces](UWidget* Widget)
		{
			if (Widget->GetClass()->ImplementsInterface(UProcedureInterface::StaticClass()))
			{
				ProcedureInterfaces.Add(Cast<IProcedureInterface>(Widget));
			}
		}
	);

	return ProcedureInterfaces;
}

void UScreenWidgetManager::ActiveWidget(UUserWidgetBase* InWidget, FSimpleMulticastDelegate OnFinish)
{
	FSimpleMulticastDelegate OnActiveFinish;
	OnActiveFinish.AddLambda([this, &InWidget, OnFinish]()
		{
			FScreenWidgetDelegates::OnWidgetOpen.Broadcast(InWidget);
			OnFinish.Broadcast();
		}
	);

	GetManager<UProcedureManager>()->RegisterProcedureHandle(GetProcedureInterfaceHandles(InWidget, true), OnActiveFinish);
}

void UScreenWidgetManager::InactiveWidget(UUserWidgetBase* InWidget, FSimpleMulticastDelegate OnFinish)
{
	FSimpleMulticastDelegate OnInactiveFinish;
	OnInactiveFinish.AddLambda([this, &InWidget, OnFinish]()
		{
			FScreenWidgetDelegates::OnWidgetClose.Broadcast(InWidget);
			OnFinish.Broadcast();
		}
	);

	GetManager<UProcedureManager>()->RegisterProcedureHandle(GetProcedureInterfaceHandles(InWidget, false), OnInactiveFinish);
}

void UScreenWidgetManager::SwitchGameMenu(UGameMenuSetting* InGameMenuSetting)
{
	if (!IsValid(InGameMenuSetting))
	{
		DEBUG(Debug_UI, Error, TEXT("GameMenuSetting Is NULL"))
		return;
	}

	if (IsValid(GameMenu))
	{
		for (const auto& Slot : Slots)
		{
			Slot.Value->ClearChildren();
		}

		MenuGenerateInfos.Reset();
		CurrentActiveMenuTag = FGameplayTag::EmptyTag;
		LastActiveMenuTag = FGameplayTag::EmptyTag;

		MenuSelectionChangedHandle.Reset();
		TargetMenuSelection.Reset();
		UpdateMenuSelectionHandle.Invalidate();
		TargetMenuSelectionIndex = 0;

		FScreenWidgetDelegates::OnMenuSelectionChanged.RemoveAll(this);
		FScreenWidgetDelegates::OnMenuCleanup.Broadcast();
	}

	/* Generate Root Menu */
	GameMenu = InGameMenuSetting;
	if (const FMenuContainerInfo* MenuContainerInfo = GameMenu->GetRootContainerInfo())
	{
		MenuSelectionChangedHandle = FScreenWidgetDelegates::OnMenuSelectionChanged.AddUObject(this, &UScreenWidgetManager::OnMenuSelectionChanged);
		GenerateMenu(*MenuContainerInfo);
		FScreenWidgetDelegates::OnMenuGenerated.Broadcast();
	}
}

void UScreenWidgetManager::SelectMenu(const FGameplayTag InMenuTag)
{
	for (auto& MenuGenerateInfo : MenuGenerateInfos)
	{
		if (MenuGenerateInfo.HasMenuInfo(InMenuTag))
		{
			MenuGenerateInfo.SelectMenu(InMenuTag);
			return;
		}
	}
}

void UScreenWidgetManager::DeselectMenu(const FGameplayTag InMenuTag)
{
	for (auto& MenuGenerateInfo : MenuGenerateInfos)
	{
		if (MenuGenerateInfo.HasMenuInfo(InMenuTag))
		{
			MenuGenerateInfo.DeselectMenu(InMenuTag);
			return;
		}
	}
}

bool UScreenWidgetManager::GetMenuContainerInfo(const FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo)
{
	if (const FMenuContainerInfo* MenuContainerInfo = GameMenu->GetContainerInfo(InMenuTag))
	{
		OutMenuContainerInfo = *MenuContainerInfo;
		return true;
	}

	return false;
}

bool UScreenWidgetManager::GetMenuParentContainerInfo(FGameplayTag InMenuTag, FMenuContainerInfo& OutMenuContainerInfo)
{
	if (const FMenuContainerInfo* MenuContainerInfo = GameMenu->GetParentContainerInfo(InMenuTag))
	{
		OutMenuContainerInfo = *MenuContainerInfo;
		return true;
	}

	return false;
}

bool UScreenWidgetManager::GetMenuGenerateInfo(const FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo)
{
	if (const FMenuContainerInfo* MenuContainerInfo = GameMenu->GetContainerInfo(InMenuTag))
	{
		if (const FMenuGenerateInfo* FoundMenuGenerateInfo = MenuGenerateInfos.FindByKey(*MenuContainerInfo))
		{
			OutMenuGenerateInfo = *FoundMenuGenerateInfo;
			return true;
		}
	}

	return false;
}

bool UScreenWidgetManager::GetMenuParentGenerateInfo(FGameplayTag InMenuTag, FMenuGenerateInfo& OutMenuGenerateInfo)
{
	if (const FMenuContainerInfo* MenuContainerInfo = GameMenu->GetParentContainerInfo(InMenuTag))
	{
		if (const FMenuGenerateInfo* FoundMenuGenerateInfo = MenuGenerateInfos.FindByKey(*MenuContainerInfo))
		{
			OutMenuGenerateInfo = *FoundMenuGenerateInfo;
			return true;
		}
	}

	return false;
}

UMenuStyle* UScreenWidgetManager::GetMenuStyle(const FGameplayTag InMenuTag)
{
	FMenuGenerateInfo FoundMenuGenerateInfo;
	if (GetMenuParentGenerateInfo(InMenuTag, FoundMenuGenerateInfo))
	{
		if (UMenuStyle* FoundMenuStyle = FoundMenuGenerateInfo.GetMenuStyle(InMenuTag))
		{
			return FoundMenuStyle;
		}
	}

	return nullptr;
}

UMenuStyle* UScreenWidgetManager::GetParentMenuStyle(const FGameplayTag InMenuTag)
{
	return GetMenuStyle(InMenuTag.RequestDirectParent());
}

TArray<UMenuStyle*> UScreenWidgetManager::GetAllMenuStyle()
{
	TArray<UMenuStyle*> Result;
	for (auto& MenuGenerateInfo : MenuGenerateInfos)
	{
		Result.Append(MenuGenerateInfo.MenuStyles);
	}
	return Result;
}

void UScreenWidgetManager::GenerateMenu(FMenuContainerInfo InMenuContainerInfo)
{
	UMenuContainer* MenuContainer;
	if (InMenuContainerInfo.MenuContainer)
	{
		MenuContainer = DuplicateObject(InMenuContainerInfo.MenuContainer, InMenuContainerInfo.MenuContainer->GetOuter());
	}
	else
	{
		MenuContainer = CreateWidget<UMenuContainer>(GetWorld());
	}

	/* 创建按钮组管理状态的切换 */
	UCommonButtonGroup* NewCommonButtonGroup = NewObject<UCommonButtonGroup>(this);
	FMenuGenerateInfo NewMenuGenerateInfo = FMenuGenerateInfo(NewCommonButtonGroup, InMenuContainerInfo);

	/* 先添加到屏幕，初始化容器 */
	OpenUserWidget(MenuContainer);

	MenuContainer->PreConstructMenuStyle(InMenuContainerInfo.MenuInfos);

	/* 构建菜单样式 */
	TArray<UMenuStyle*> MenuStyleArr;
	for (const auto& MenuInfo : InMenuContainerInfo.MenuInfos)
	{
		/* MenuInfo的按钮样式将覆盖MenuContainer的按钮样式 */
		UMenuStyle* MenuStyle = nullptr;
		if (IsValid(InMenuContainerInfo.MenuStyle))
		{
			MenuStyle = CreateWidget<UMenuStyle>(GetWorld(), InMenuContainerInfo.MenuStyle);
		}
		else if (IsValid(MenuInfo.MenuStyleOverride))
		{
			MenuStyle = DuplicateObject(MenuInfo.MenuStyleOverride, MenuInfo.MenuStyleOverride->GetOuter());
		}
		else
		{
			/* 即使没有表现样式，也提供容器来触发事件，使用SelectMenu/DeselectMenu */
			MenuStyle = CreateWidget<UMenuStyle>(GetWorld());
		}

		/* 只有当样式有效，才添加该按钮 */
		if (IsValid(MenuStyle))
		{
			NewMenuGenerateInfo.MenuStyles.Add(MenuStyle);
			MenuStyle->NativeOnCreate();

			/* 添加到CommonButtonGroup */
			NewMenuGenerateInfo.CommonButtonGroup->AddWidget(MenuStyle);

			MenuContainer->ConstructMenuStyle(MenuStyle);
			MenuStyle->NativeConstructMenuStyle(MenuInfo);
			MenuStyle->NativeOnActived();
			MenuStyleArr.Add(MenuStyle);
		}
	}

	MenuContainer->PostConstructMenuStyle(MenuStyleArr);

	MenuGenerateInfos.Add(NewMenuGenerateInfo);

	/* bIsSelectionRequired=true 时将不能在选中状态下再次点击取消选中 */
	NewCommonButtonGroup->SetSelectionRequiredIndex(InMenuContainerInfo.SelectionRequiredIndex);
	NewCommonButtonGroup->UpdateSelectionRequired(InMenuContainerInfo.bIsSelectionRequired);
	for (const auto& MenuStyle : MenuStyleArr)
	{
		MenuStyle->SetIsToggleable(InMenuContainerInfo.bIsSelectionRequired ? false : InMenuContainerInfo.bIsToggleable);
	}

	OnMenuGenerate.Broadcast(NewMenuGenerateInfo);
}

void UScreenWidgetManager::UpdateActiveMenutag()
{
	TArray<FGameplayTag> MenuTags;
	TargetMenuSelection.GenerateKeyArray(MenuTags);

	/* 处理 LastActiveMenuTag 和 CurrentActiveMenuTag 的更新 */
	if (MenuTags.Num() == 1)
	{
		if (TargetMenuSelection.FindRef(MenuTags[0]))
		{
			LastActiveMenuTag = CurrentActiveMenuTag;
			CurrentActiveMenuTag = MenuTags[0];
		}
		else
		{
			LastActiveMenuTag = CurrentActiveMenuTag;

			if (GetParentMenuStyle(MenuTags[0]))
			{
				const FGameplayTag ParentMenuTag = GetParentMenuStyle(MenuTags[0])->GetMenuInfo().MenuTag;
				CurrentActiveMenuTag = ParentMenuTag.IsValid() ? ParentMenuTag : FGameplayTag::EmptyTag;
			}
			else
			{
				CurrentActiveMenuTag = FGameplayTag::EmptyTag;
			}
		}
	}
	else
	{
		LastActiveMenuTag = MenuTags[0];

		const FGameplayTag LastMenuTag = MenuTags.Last();
		if (TargetMenuSelection.FindRef(LastMenuTag))
		{
			CurrentActiveMenuTag = LastMenuTag;
		}
		else
		{
			CurrentActiveMenuTag = FGameplayTag::EmptyTag;
		}
	}
}

void UScreenWidgetManager::OnMenuSelectionChanged(FMenuInfo InMenuInfo, bool bSelection)
{
	DEBUG(Debug_UI, Warning, TEXT("MenuInfo : %s,Seletion : %d"), *InMenuInfo.MenuMainName.ToString(), bSelection)

	if (bSelection)
	{
		TargetMenuSelection.Add(InMenuInfo.MenuTag, true);
	}
	else
	{
		FMenuGenerateInfo MenuGenerateInfo;
		if (GetMenuGenerateInfo(InMenuInfo.MenuTag, MenuGenerateInfo))
		{
			MenuGenerateInfo.CommonButtonGroup->SetSelectionRequired(false);
			MenuGenerateInfo.CommonButtonGroup->DeselectAll();
		}

		TargetMenuSelection.Add(InMenuInfo.MenuTag, false);
	}

	if (!UpdateMenuSelectionHandle.IsValid() && !TargetMenuSelection.IsEmpty())
	{
		UpdateMenuSelectionHandle = GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UScreenWidgetManager::HandleMenuSelectionChangedNextTick);
	}
}

void UScreenWidgetManager::HandleMenuSelectionChangedNextTick()
{
	UpdateActiveMenutag();

	for (const auto& Menu : GetAllMenuStyle())
	{
		Menu->SetEnableInteraction(false);
	}

	DEBUG(Debug_UI, Warning, TEXT("CurrentActiveMenuTag : %s , LastActiveMenuTag : %s"), *CurrentActiveMenuTag.ToString(), *LastActiveMenuTag.ToString())
	HandleMenuSelectionChanged();
}

void UScreenWidgetManager::HandleMenuSelectionChanged()
{
	TArray<FGameplayTag> MenuTags;
	TargetMenuSelection.GenerateKeyArray(MenuTags);

	if (MenuTags.IsValidIndex(TargetMenuSelectionIndex))
	{
		const FGameplayTag MenuTag = MenuTags[TargetMenuSelectionIndex];
		const bool bSelection = TargetMenuSelection.FindRef(MenuTag);

		FSimpleMulticastDelegate OnHandleMenuFinish;
		OnHandleMenuFinish.AddLambda([this]()
			{
				HandleMenuSelectionChangedOnceFinish();
			}
		);

		if (bSelection)
		{
			ActiveMenu(MenuTag, OnHandleMenuFinish);
		}
		else
		{
			InactiveMenu(MenuTag, OnHandleMenuFinish);
		}
	}
	else
	{
		HandleMenuSelectionChangedOnceFinish();
	}
}

void UScreenWidgetManager::ActiveMenu(FGameplayTag InMenuTag, FSimpleMulticastDelegate OnFinish)
{
	if (const FMenuContainerInfo* MenuContainerInfo = GameMenu->GetContainerInfo(InMenuTag))
	{
		GenerateMenu(*GameMenu->GetContainerInfo(InMenuTag));
	}

	for (const auto& Menu : GetAllMenuStyle())
	{
		Menu->SetEnableInteraction(false);
	}

	if (UMenuStyle* MenuStyle = GetMenuStyle(InMenuTag))
	{
		FSimpleMulticastDelegate OnHandleFinish;
		OnHandleFinish.AddLambda([OnFinish]()
			{
				OnFinish.Broadcast();
			}
		);

		MenuStyle->ResponseButtonEvent(ECommonButtonResponseEvent::OnSelected, OnHandleFinish);
		return;
	}

	OnFinish.Broadcast();
}

void UScreenWidgetManager::InactiveMenu(FGameplayTag InMenuTag, FSimpleMulticastDelegate OnFinish)
{
	FMenuGenerateInfo MenuGenerateInfo;
	if (GetMenuGenerateInfo(InMenuTag, MenuGenerateInfo))
	{
		for (const auto& GarbageMenuStyle : MenuGenerateInfo.MenuStyles)
		{
			GarbageMenuStyle->NativeOnDestroy();
			GarbageMenuStyle->RemoveFromParent();
			GarbageMenuStyle->MarkAsGarbage();
		}

		CloseUserWidget(MenuGenerateInfo.MenuContainerInfo.MenuContainer);
		MenuGenerateInfos.Remove(MenuGenerateInfo);
	}

	if (UMenuStyle* MenuStyle = GetMenuStyle(InMenuTag))
	{
		MenuStyle->ResponseButtonEvent(ECommonButtonResponseEvent::OnDeselected, OnFinish);
		return;
	}

	OnFinish.Broadcast();
}

void UScreenWidgetManager::HandleMenuSelectionChangedOnceFinish()
{
	if (!UpdateMenuSelectionHandle.IsValid())
	{
		return;
	}

	DEBUG(Debug_UI, Warning, TEXT(""))

	TargetMenuSelectionIndex++;
	if (TargetMenuSelectionIndex < TargetMenuSelection.GetMaxIndex())
	{
		HandleMenuSelectionChanged();
	}
	else
	{
		HandleMenuSelectionChangedFinish();
	}
}

void UScreenWidgetManager::HandleMenuSelectionChangedFinish()
{
	TargetMenuSelection.Reset();
	TargetMenuSelectionIndex = 0;
	UpdateMenuSelectionHandle.Invalidate();

	for (const auto& Menu : GetAllMenuStyle())
	{
		Menu->SetEnableInteraction(true);
	}

	DEBUG(Debug_UI, Warning, TEXT(""))
	DEBUG(Debug_UI, Warning, TEXT("===================="))
}

#undef LOCTEXT_NAMESPACE
