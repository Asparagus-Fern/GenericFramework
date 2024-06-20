// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureManager.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

#include "Manager/ManagerCollection.h"
#include "Procedure/GameplayProcedure.h"
#include "StaticFunctions/StaticFunctions_Object.h"

#define LOCTEXT_NAMESPACE "UProcedureManager"

UProcedureManager::UProcedureManager()
{
	DisplayName = LOCTEXT("DisplayName", "Procedure Manager");
	ProcedureOrder = -1;

	EditorWorld = nullptr;

	LastGameplayProcedure = EGameplayProcedure::None;
	CurrentGameplayProcedure = EGameplayProcedure::None;

	GameplayProcedureClass.Add(EGameplayProcedure::GameLoading);
	GameplayProcedureClass.Add(EGameplayProcedure::MainMenu);
	GameplayProcedureClass.Add(EGameplayProcedure::Play);
	GameplayProcedureClass.Add(EGameplayProcedure::Pause);
	GameplayProcedureClass.Add(EGameplayProcedure::Exit);
}

void UProcedureManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UProcedureManager::OnPostWorldInitialization);
	FWorldDelegates::OnWorldCleanup.AddUObject(this, &UProcedureManager::OnWorldCleanup);

#if WITH_EDITOR
	GEditor->OnEditorClose().AddUObject(this, &UProcedureManager::OnEditorClose);
#endif
}

UProcedureManager* UProcedureManager::Get()
{
	return FManagerCollection::Get()->GetManager<UProcedureManager>();
}

void UProcedureManager::OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues InitializationValues)
{
	/* todo:不同世界类型的处理 */
	if (InWorld->WorldType != EWorldType::Game && InWorld->WorldType != EWorldType::PIE && InWorld->WorldType != EWorldType::Editor)
	{
		return;
	}

	/* 保存Editor世界 */
#if WITH_EDITORONLY_DATA
	if (InWorld->WorldType == EWorldType::Editor)
		EditorWorld = InWorld;
#endif

	/* Game和PIE在该代理之后激活 */
	InWorld->OnWorldMatchStarting.AddUObject(this, &UProcedureManager::OnWorldMatchStarting, InWorld);

#if WITH_EDITOR
	RefreshManagerOrders();

	/* PIE运行退出Editor Manager */
	ProcessManagerOrders
	(false,
	 [](UCoreManager* InCoreManager)
	 {
		 if (InCoreManager->GetIsActive() && InCoreManager->IsEditorManager())
		 {
			 InCoreManager->NativeOnInactived();
			 InCoreManager->ManagerWorld = nullptr;
			 DEBUG_LOG(Debug_Manager, Log, TEXT("Manager Inactived : %s"), *InCoreManager->GetName())
		 }
	 }
	);

	/* 编辑器打开激活Editor Manager */
	ProcessManagerOrders
	(true,
	 [InWorld](UCoreManager* InCoreManager)
	 {
		 if (!InCoreManager->GetIsActive() && InCoreManager->IsEditorManager() && InWorld->WorldType == EWorldType::Editor)
		 {
			 bool a = InCoreManager->GetClass()->ImplementsInterface(UProcedureBaseInterface::StaticClass());
			 bool b = InCoreManager->GetClass()->ImplementsInterface(UProcedureInterface::StaticClass());
			 bool c = InCoreManager->GetClass()->ImplementsInterface(UProcedureManagerInterface::StaticClass());

			 InCoreManager->ManagerWorld = InWorld;
			 InCoreManager->NativeOnActived();
			 DEBUG_LOG(Debug_Manager, Log, TEXT("Manager Actived : %s"), *InCoreManager->GetName())
		 }
	 }
	);

#endif
}

void UProcedureManager::OnWorldMatchStarting(UWorld* InWorld)
{
	RefreshManagerOrders();

	if (InWorld->WorldType == EWorldType::Game || InWorld->WorldType == EWorldType::PIE)
	{
		/* 在游戏确定性开始后激活管理类 */
		ProcessManagerOrders
		(true,
		 [InWorld](UCoreManager* InCoreManager)
		 {
			 if (!InCoreManager->GetIsActive())
			 {
				 InCoreManager->ManagerWorld = InWorld;
				 InCoreManager->NativeOnActived();
				 DEBUG_LOG(Debug_Manager, Log, TEXT("Manager Actived : %s"), *InCoreManager->GetName())
			 }
		 }
		);

		/* 切换游戏默认流程 */
		SwitchProcedure(DefaultGameplayProcedure);
	}
}

void UProcedureManager::OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources)
{
	if (InWorld->WorldType != EWorldType::Game && InWorld->WorldType != EWorldType::PIE && InWorld->WorldType != EWorldType::Editor)
	{
		return;
	}

	/* 关闭所有的管理类 */
	ProcessManagerOrders
	(false,
	 [](UCoreManager* InCoreManager)
	 {
		 if (InCoreManager->GetIsActive())
		 {
			 InCoreManager->NativeOnInactived();
			 InCoreManager->ManagerWorld = nullptr;
			 DEBUG_LOG(Debug_Manager, Log, TEXT("Manager Inactived : %s"), *InCoreManager->GetName())
		 }
	 }
	);

	CurrentGameplayProcedure = EGameplayProcedure::None;
	LastGameplayProcedure = EGameplayProcedure::None;

#if WITH_EDITORONLY_DATA
	/* 切换编辑器世界时 */
	if (InWorld->WorldType == EWorldType::Editor)
	{
		EditorWorld = nullptr;
		return;
	}
#endif

#if WITH_EDITOR

	/* 在编辑器下退出了一个游戏世界，激活编辑器管理类 */
	ProcessManagerOrders
	(true,
	 [this](UCoreManager* InCoreManager)
	 {
		 if (!InCoreManager->GetIsActive() && InCoreManager->IsEditorManager())
		 {
			 InCoreManager->ManagerWorld = EditorWorld;
			 InCoreManager->NativeOnActived();
			 DEBUG_LOG(Debug_Manager, Log, TEXT("Manager Actived : %s"), *InCoreManager->GetName())
		 }
	 }
	);

#endif
}

void UProcedureManager::RefreshManagerOrders()
{
	ManagerOrders.Reset();
	for (auto& Manager : FManagerCollection::Get()->GetManagers())
	{
		if (!ManagerOrders.Contains(Manager->ProcedureOrder))
		{
			FManagerOrder NewManagerOrder = FManagerOrder(Manager->ProcedureOrder);
			NewManagerOrder.Managers.Add(Manager);
			ManagerOrders.Add(NewManagerOrder);
		}
		else
		{
			FManagerOrder& FindManagerOrder = *ManagerOrders.FindByKey(Manager->ProcedureOrder);
			FindManagerOrder.Managers.Add(Manager);
		}
	}
}

void UProcedureManager::ProcessManagerOrders(bool IsForwardSort, const TFunctionRef<void(UCoreManager* InManager)>& Exec)
{
	ManagerOrders.Sort
	([IsForwardSort](const FManagerOrder& A, const FManagerOrder& B)
		{
			return IsForwardSort ? (A.Order < B.Order) : (A.Order > B.Order);
		}
	);

	for (auto& ManagerOrder : ManagerOrders)
	{
		for (const auto& Manager : ManagerOrder.Managers)
		{
			Exec(Manager);
		}
	}
}

void UProcedureManager::OnEditorClose()
{
#if WITH_EDITOR
	/* 关闭所有的管理类 */
	ProcessManagerOrders
	(false,
	 [](UCoreManager* InCoreManager)
	 {
		 if (InCoreManager->GetIsActive())
		 {
			 InCoreManager->NativeOnInactived();
			 InCoreManager->ManagerWorld = nullptr;
			 DEBUG_LOG(Debug_Manager, Log, TEXT("Manager Inactived : %s"), *InCoreManager->GetName())
		 }
	 }
	);

	CurrentGameplayProcedure = EGameplayProcedure::None;
	LastGameplayProcedure = EGameplayProcedure::None;
	EditorWorld = nullptr;
#endif
}

void UProcedureManager::NativeOnActived()
{
	Super::NativeOnActived();
}

void UProcedureManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	LastGameplayProcedure = EGameplayProcedure::None;
	CurrentGameplayProcedure = EGameplayProcedure::None;
	GameplayProcedure.Reset();
}

bool UProcedureManager::SwitchProcedure(EGameplayProcedure InProcedure, bool bForce)
{
	/* 不更新流程 */
	if (CurrentGameplayProcedure == InProcedure && !bForce)
	{
		return false;
	}

	/* 广播流程切换之前 */
	FStaticFunctions_Manager::ProcessManagerInterface<UCoreManager>
	([InProcedure, this](UCoreManager* InManager)
		{
			InManager->NativePreProcedureSwitch(CurrentGameplayProcedure, InProcedure);
		}
	);

	if (UGameplayProcedure* EndGameplayProcedure = GetGameplayProcedure(CurrentGameplayProcedure))
	{
		EndGameplayProcedure->NativeOnInactived();
	}

	LastGameplayProcedure = CurrentGameplayProcedure;
	CurrentGameplayProcedure = InProcedure;

	if (UGameplayProcedure* BeginGameplayProcedure = GetGameplayProcedure(CurrentGameplayProcedure))
	{
		BeginGameplayProcedure->NativeOnActived();
	}

	/* 广播流程切换完成 */
	FStaticFunctions_Manager::ProcessManagerInterface<UCoreManager>
	([this](UCoreManager* InManager)
		{
			InManager->NativePostProcedureSwitch(CurrentGameplayProcedure);
		}
	);

	DEBUG_LOG(Debug_Manager, Log, TEXT("Switch Procedure From %s To %s"), *UEnum::GetDisplayValueAsText(LastGameplayProcedure).ToString(), *UEnum::GetDisplayValueAsText(CurrentGameplayProcedure).ToString())
	return true;
}

UGameplayProcedure* UProcedureManager::GetGameplayProcedure(EGameplayProcedure InProcedure)
{
	/* 流程不为空 */
	if (InProcedure != EGameplayProcedure::None)
	{
		UGameplayProcedure* FoundGameplayProcedure = nullptr;
		if (!GameplayProcedure.Contains(InProcedure))
		{
			/* 创建流程类实例并返回 */
			const TSoftClassPtr<UGameplayProcedure> FoundGameplayProcedureClass = GameplayProcedureClass.FindRef(InProcedure);
			if (!FoundGameplayProcedureClass.IsNull())
			{
				TSubclassOf<UGameplayProcedure> LoadGameplayProcedure = FStaticFunctions_Object::LoadClass<UGameplayProcedure>(FoundGameplayProcedureClass);
				FoundGameplayProcedure = NewObject<UGameplayProcedure>(this, LoadGameplayProcedure);
				GameplayProcedure.Add(InProcedure, FoundGameplayProcedure);
			}
			/* 返回流程类实例的缓存 */
			else
			{
				FoundGameplayProcedure = GameplayProcedure.FindRef(InProcedure);
			}
		}

		return FoundGameplayProcedure;
	}
	return nullptr;
}

#undef LOCTEXT_NAMESPACE
