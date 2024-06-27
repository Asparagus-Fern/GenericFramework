// Fill out your copyright notice in the Description page of Project Settings.

#include "ActiveNodeSubsystem.h"
#include "ActiveNode.h"
#include "ActiveNodeComponent.h"
#include "ActiveNodeManager.h"
#include "EngineUtils.h"
#include "Components/GameFrameworkComponent.h"
#include "Manager/ManagerGlobal.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ActiveNode, "ActiveNode");

UActiveNodeSubsystem::UActiveNodeSubsystem()
	: Super()
	  , bBreathe(false)
{
}

UActiveNodeSubsystem::ThisClass* UActiveNodeSubsystem::Get(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	return World->GetSubsystem<ThisClass>();
}

void UActiveNodeSubsystem::OnWorldMatchStarting()
{
	// todo : 没有收集到活跃点, 但还有一种可能 : 如果是后期动态 Spawn Register 进来的  (但现在还没有为该系统提供 Register 相关的接口...)
	if (NodeMappings.IsEmpty())
		return;

	if (GetManager<UActiveNodeManager>()->bAutoLogin)
	{
		check(CurrentNode == nullptr);

		// todo : 确定要进行登录的 Tag... , 还需要一个重载Tag的配置来覆盖默认节点Tag
		FGameplayTag LoginTag;
		Entry(LoginTag);
	}
}

bool UActiveNodeSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// 如果有项目通过这个类进行了派生, 我们就不在创建这个类.
	TArray<UClass*> DerivedClasses;
	GetDerivedClasses(GetClass(), DerivedClasses);

	if (!DerivedClasses.IsEmpty())
	{
		return false;
	}

	return Super::ShouldCreateSubsystem(Outer);
}

void UActiveNodeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 这个时候 UWorld 还没有完全初始化..

	// FWorldDelegates::LevelAddedToWorld.AddRaw(this, &UActiveNodeSubsystem::HandleOnActorAddToWorld);
}

void UActiveNodeSubsystem::Deinitialize()
{
	Super::Deinitialize();

	Exit();
	NodeMappings.Empty();
}

void UActiveNodeSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UActiveNodeSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// 绑定世界确定性开始的代理, 这将发生在 所有 Actor BeginPlay 之后, 稍后将处理具体的登录活跃节点.
	InWorld.OnWorldMatchStarting.AddUObject(this, &ThisClass::OnWorldMatchStarting);

	// 收集所有已知的活跃节点.

	// todo @ChangQing : 2024.03.08， 修复大世界加载子世界问题...
	/*for(TActorIterator<AActiveNode> It(&InWorld); It; ++It)
	{
		FGameplayTag NodeTag = It->NodeTag;
		
		if(ensureMsgf(NodeTag.IsValid(), TEXT("The node named %s has an invalid Tag"), *It->GetName()))
		{
			if(ensureMsgf(!NodeMappings.Contains(NodeTag), TEXT("Multiple active nodes with Tag '%s' detected"), *NodeTag.ToString()))
			{
				auto Node = NodeMappings.Emplace(NodeTag, *It);

				// 处理所有活跃节点组件的登记事务.
				ProcessingNodeInterfaceComponents(Node, [](UActiveNodeComponent* Component)  {
					IActiveNodeInterface::Execute_RegisterNode(Component);
				});

				// 处理活跃节点的登记事务.
				IActiveNodeInterface::Execute_RegisterNode(Node);
				
				// todo : 预留 Game Feature 动态插件的能力.
			}
		}
	}*/
}

void UActiveNodeSubsystem::OnWorldComponentsUpdated(UWorld& World)
{
	Super::OnWorldComponentsUpdated(World);
}

void UActiveNodeSubsystem::UpdateStreamingState()
{
	Super::UpdateStreamingState();
}

bool UActiveNodeSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	// 我们只在游戏或是PIE模式下工作.
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

TStatId UActiveNodeSubsystem::GetStatId() const
{
	return TStatId();
}

void UActiveNodeSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(CurrentNode))
	{
		bBreathe = true;
	}

	if (!bBreathe)
		return;

	if (!IsValid(CurrentNode) && !IsValid(AccessibleNode))
	{
		Exit();
	}

	if (IsCurrentNodeActive() && !GetManager<UActiveNodeManager>()->bBlockUpdate)
	{
		if (!CurrentNode->bAlwaysUpdate)
			return;

		if (CurrentNode->bComponentUpdate)
		{
			ProcessingNodeInterfaceComponents
			(
				CurrentNode,
				[&DeltaTime](UActiveNodeComponent* InComponent)
				{
					if (IActiveNodeInterface::Execute_CanUpdate(InComponent))
					{
						IActiveNodeInterface::Execute_UpdateNode(InComponent, DeltaTime);
					}
				}
			);
		}

		if (IActiveNodeInterface::Execute_CanUpdate(CurrentNode))
		{
			IActiveNodeInterface::Execute_UpdateNode(CurrentNode, DeltaTime);
		}
	}
}

bool UActiveNodeSubsystem::IsTickable() const
{
	return true;
}

AActiveNode* UActiveNodeSubsystem::GetCurrentActiveNode() const
{
	return CurrentNode;
}

FGameplayTag UActiveNodeSubsystem::GetCurrentActiveNodeTag()
{
	return CurrentNode->NodeTag;
}

TMap<FGameplayTag, TObjectPtr<AActiveNode>> UActiveNodeSubsystem::GetNodeMappings() const
{
	return NodeMappings;
}

void UActiveNodeSubsystem::RegisterNode(FGameplayTag InTag, AActiveNode* InNode)
{
	if (InTag.IsValid())
	{
		if (!NodeMappings.Contains(InTag))
		{
			const auto Node = NodeMappings.Emplace(InTag, InNode);

			ProcessingNodeInterfaceComponents
			(
				Node,
				[](UActiveNodeComponent* Component)
				{
					IActiveNodeInterface::Execute_RegisterNode(Component);
				}
			);

			IActiveNodeInterface::Execute_RegisterNode(Node);

			UE_LOG(LogActiveNodeSystem, Log, TEXT("Active Node Register : [%s]"), *InTag.ToString());

			if (OnActionNodeRegister.IsBound())
			{
				OnActionNodeRegister.Broadcast(InTag);
			}
		}
	}
}

void UActiveNodeSubsystem::UnRegisterNode(FGameplayTag InTag)
{
	if (InTag.IsValid())
	{
		if (const auto Node = NodeMappings.Find(InTag))
		{
			ProcessingNodeInterfaceComponents
			(
				*Node,
				[](UActiveNodeComponent* Component)
				{
					IActiveNodeInterface::Execute_UnRegisterNode(Component);
				}
			);

			IActiveNodeInterface::Execute_UnRegisterNode(*Node);

			NodeMappings.Remove(InTag);

			UE_LOG(LogActiveNodeSystem, Log, TEXT("Active node Unregister : [%s]"), *InTag.ToString());

			if (OnActionNodeUnRegister.IsBound())
			{
				OnActionNodeUnRegister.Broadcast(InTag);
			}
		}
	}
}

bool UActiveNodeSubsystem::ChangeActiveNodeTo(const UObject* WorldContextObject, FGameplayTag InTag, bool bReInit)
{
	return ThisClass::Get(WorldContextObject)->ChangeNode(InTag, bReInit);
}

AActiveNode* UActiveNodeSubsystem::FindActiveNode(const UObject* WorldContextObject, const FGameplayTag InTag, const TSubclassOf<AActiveNode> InClass)
{
	if (AActiveNode* FoundNode = ThisClass::Get(WorldContextObject)->FindActiveNode(InTag))
	{
		if (FoundNode->IsA(InClass))
		{
			return FoundNode;
		}
	}

	return nullptr;
}

AActiveNode* UActiveNodeSubsystem::FindActiveNode(const FGameplayTag& InTag)
{
	if (CheckTag(InTag))
	{
		return NodeMappings.Contains(InTag) ? NodeMappings[InTag] : nullptr;
	}

	return nullptr;
}

bool UActiveNodeSubsystem::ChangeNode(const FGameplayTag& InTag, bool bReInit)
{
	if (!CheckTag(InTag))
	{
		return false;
	}

	// 如果当前没有可用的活跃点, 那么尝试进入这个指定 Tag 的活跃点.
	if (!IsValid(CurrentNode))
	{
		UE_LOG(LogActiveNodeSystem, Log, TEXT("There is no active node at the moment, go directly to the '%s' node"), *InTag.ToString())
		return Entry(InTag);
	}

	if (InTag == CurrentNode->NodeTag)
	{
		ReLoginNode();
		return true;
	}

	AActiveNode* ChangeNode = FindActiveNode(InTag);

	if (!ensureMsgf(ChangeNode, TEXT("Change active node faild. not found '%s' node"), *InTag.ToString()))
	{
		return false;
	}

	// 这是一个可达的目标节点, 确保执行 LogoutNode 不会进行完全登出(Exit).
	AccessibleNode = ChangeNode;

	// 处理即将切换的节点所有组件的预切换接口事件.
	ProcessingNodeInterfaceComponents
	(
		ChangeNode,
		[this](UActiveNodeComponent* Component)
		{
			IActiveNodeInterface::Execute_PreChangeNode(Component, CurrentNode);
		}
	);

	IActiveNodeInterface::Execute_PreChangeNode(ChangeNode, ChangeNode);
	ChangeNode->OnNodePreChanged.Broadcast(ChangeNode, CurrentNode);
	OnActiveNodePreChange.Broadcast(ChangeNode, CurrentNode, bReInit);

	// 登出当前的节点.
	LogoutNode();

	// 登录目标节点.
	if (LoginNode(ChangeNode, bReInit))
	{
		AccessibleNode = nullptr;

		// 处理即将切换的节点所有组件的预切换接口事件.
		ProcessingNodeInterfaceComponents
		(
			ChangeNode,
			[](UActiveNodeComponent* Component)
			{
				IActiveNodeInterface::Execute_PostChangeNode(Component);
			}
		);

		IActiveNodeInterface::Execute_PostChangeNode(ChangeNode);
		ChangeNode->OnNodePostChanged.Broadcast(ChangeNode);
		OnActiveNodePostChange.Broadcast(ChangeNode);
		return true;
	}

	AccessibleNode = nullptr;
	return false;
}

bool UActiveNodeSubsystem::Entry(const FGameplayTag& InTag)
{
	FGameplayTag LoginTag = InTag;

	if (!LoginTag.IsValid())
	{
		LoginTag = GetManager<UActiveNodeManager>()->DefaultNodeTag;
	}

#if WITH_EDITOR
	// 没有合适 LoginTag , 如果是 PIE, 简单处理一下.
	if (!LoginTag.IsValid())
	{
		TArray<FGameplayTag> NodeTags;
		NodeMappings.GetKeys(NodeTags);
		if (!NodeTags.IsEmpty())
		{
			LoginTag = NodeTags[0];
			UE_LOG(LogActiveNodeSystem, Error, TEXT("There is no valid default active node tag, please check the default/override active node configuration"));
			UE_LOG(LogActiveNodeSystem, Warning, TEXT("Enter the nearest reachable active point '%s', please repair the configuration in time."), *LoginTag.ToString())
		}
	}
#endif

	if (!LoginTag.IsValid())
	{
		ensureMsgf(false, TEXT("Try to enter the active point, but there are no active points available"));
		return false;
	}

	AActiveNode* FoundNode = FindActiveNode(LoginTag);

	if (ensureMsgf(IsValid(FoundNode), TEXT("Entry active node faild. not found '%s' node"), *LoginTag.ToString()))
	{
		if (LoginNode(FoundNode))
		{
			OnEntryActiveNodeSystem.Broadcast();
			return true;
		}
	}

	return false;
}

void UActiveNodeSubsystem::Exit()
{
	if (IsValid(CurrentNode))
	{
		LogoutNode();
	}

	bBreathe = false;

	// 通知所有的活跃点都已经退出了.
	OnLeaveActiveNodeSystem.Broadcast();
}

void UActiveNodeSubsystem::InitNode(AActiveNode* InNode, bool bReInit)
{
	ensure(InNode);

	// 阻止活跃中的节点.
	if (ensureMsgf(!InNode->bActive, TEXT("Attempt to initialize the node '%s'"), *InNode->NodeTag.ToString()))
	{
		// 对于没有初始化的节点强制该节点进行初始化操作.
		if (bReInit || !InNode->bInitialized)
		{
			InNode->bInitialized = false;

			// 处理这个节点所有组件的初始化接口事件.
			ProcessingNodeInterfaceComponents(InNode, [](UActiveNodeComponent* InComponent)
			                                  {
				                                  IActiveNodeInterface::Execute_InitNode(InComponent);
			                                  }
			);

			IActiveNodeInterface::Execute_InitNode(InNode);
			InNode->bInitialized = true;
			InNode->OnNodeInit.Broadcast(InNode);
		}
	}
}

bool UActiveNodeSubsystem::LoginNode(AActiveNode* InNode, bool bReInit)
{
	if (!ensureMsgf(InNode, (TEXT("Login failed, there are no valid login node"))))
		return false;

	InitNode(InNode, bReInit);

	// 处理这个节点所有组件的登录接口事件.
	ProcessingNodeInterfaceComponents(InNode, [](UActiveNodeComponent* InComponent)
	                                  {
		                                  IActiveNodeInterface::Execute_LoginNode(InComponent);
	                                  }
	);

	CurrentNode = InNode;
	IActiveNodeInterface::Execute_LoginNode(InNode);
	InNode->OnNodeLogin.Broadcast(InNode);
	OnActiveNodeLogin.Broadcast(InNode);
	InNode->bActive = true;
	return true;
}

void UActiveNodeSubsystem::LogoutNode()
{
	if (IsValid(CurrentNode))
	{
		// 先让这个节点失去活跃, 不再检查它的更新操作.
		CurrentNode->bActive = false;

		// 处理这个节点所有组件的登出接口事件.
		ProcessingNodeInterfaceComponents
		(
			CurrentNode,
			[](UActiveNodeComponent* InComponent)
			{
				IActiveNodeInterface::Execute_LogoutNode(InComponent);
			}
		);

		IActiveNodeInterface::Execute_LogoutNode(CurrentNode);
		CurrentNode->OnNodeLogout.Broadcast(CurrentNode);
		CurrentNode = nullptr;
	}
}

void UActiveNodeSubsystem::ReLoginNode(const UObject* WorldContextObject, bool bReInit)
{
	ThisClass::Get(WorldContextObject)->ReLoginNode(bReInit);
}

void UActiveNodeSubsystem::ReLoginNode(bool bReInit)
{
	if (IsValid(CurrentNode))
	{
		AccessibleNode = CurrentNode;

		LogoutNode();

		// 永不失败!
		check(LoginNode(AccessibleNode, bReInit));

		// 处理这个节点所有组件的重新登录接口事件.
		ProcessingNodeInterfaceComponents(CurrentNode, [](UActiveNodeComponent* InComponent)
		                                  {
			                                  IActiveNodeInterface::Execute_ReLoginNode(InComponent);
		                                  }
		);

		IActiveNodeInterface::Execute_ReLoginNode(CurrentNode);
		CurrentNode->OnNodeReLogin.Broadcast(CurrentNode);
		AccessibleNode = nullptr;
	}
}

void UActiveNodeSubsystem::LogOut(const UObject* WorldContextObject)
{
	UActiveNodeSubsystem* ActiveNodeSubsystem = UActiveNodeSubsystem::Get(WorldContextObject);
	check(ActiveNodeSubsystem);
	ActiveNodeSubsystem->LogoutNode();
}

void UActiveNodeSubsystem::ProcessingNodeInterfaceComponents(AActiveNode* InNode, const TFunctionRef<void(UActiveNodeComponent* InComponent)>& InterfaceCall)
{
	for (TComponentIterator<UActiveNodeComponent> CompIt(InNode); CompIt; ++CompIt)
	{
		if (CompIt->IsRegistered() && CompIt->IsActive())
		{
			InterfaceCall(*CompIt);
		}
	}
}

bool UActiveNodeSubsystem::CheckTag(const FGameplayTag& InTag) const
{
	if (!InTag.IsValid() || !InTag.MatchesTag(TAG_ActiveNode))
	{
		UE_LOG(LogActiveNodeSystem, Error, TEXT("ActiveNodeSystem -> invalide tag!"))
		return false;
	}

	return true;
}

bool UActiveNodeSubsystem::IsCurrentNodeActive() const
{
	return IsValid(CurrentNode) && CurrentNode->bInitialized && CurrentNode->bActive;
}
