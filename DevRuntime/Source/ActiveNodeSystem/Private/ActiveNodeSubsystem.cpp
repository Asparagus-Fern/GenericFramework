// Fill out your copyright notice in the Description page of Project Settings.

#include "ActiveNodeSubsystem.h"
#include "ActiveNode.h"
#include "ActiveNodeSettings.h"
#include "EngineUtils.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ActiveNode, "ActiveNode");

UActiveNodeSubsystem::UActiveNodeSubsystem()
	: Super()
	, bBreathe(false)
{
}

UActiveNodeSubsystem::ThisClass* UActiveNodeSubsystem::Get(const UWorld* InWorld)
{
	check(InWorld);
	return InWorld->GetSubsystem<ThisClass>();
}

bool UActiveNodeSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// 如果有项目通过这个类进行了派生, 我们就不在创建这个类.
	TArray<UClass*> DerivedClasses;
	GetDerivedClasses(GetClass(), DerivedClasses);
	
	if(!DerivedClasses.IsEmpty())
	{
		return false;
	}
	
	return Super::ShouldCreateSubsystem(Outer);
}

void UActiveNodeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 这个时候 UWorld 还没有完全初始化..
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

	// todo : 在这里工作 TActorIterator 访问不到 LevelInstance 所带来的所有Actor对象 -> 移动到 OnWorldBeginPlay 阶段
}

void UActiveNodeSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	for(TActorIterator<AActiveNode> It(&InWorld); It; ++It)
	{
		FGameplayTag NodeTag = It->NodeTag;
		
		if(ensureMsgf(NodeTag.IsValid(), TEXT("The node named %s has an invalid Tag"), *It->GetName()))
		{
			if(ensureMsgf(!NodeMappings.Contains(NodeTag), TEXT("Multiple active nodes with Tag '%s' detected"), *NodeTag.ToString()))
			{
				auto Node = NodeMappings.Emplace(NodeTag, *It);
				// todo : 预留 Game Feature 动态插件的能力.
			}
		}
	}

	// todo : 没有收集到活跃点, 但还有一种可能 : 如果是后期动态 Spawn Register 进来的  (但现在还没有为该系统提供 Register 相关的接口...) 
	if(NodeMappings.IsEmpty())
		return;
	
	if(UActiveNodeSettings::Get()->bAutoLogin)
	{
		check(CurrentNode == nullptr);
		
		// todo : 确定要进行登录的 Tag... , 还需要一个重载Tag的配置来覆盖默认节点Tag
		FGameplayTag LoginTag;
		Entry(LoginTag);
	}
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

	if(IsValid(CurrentNode))
	{
		bBreathe = true;
	}

	if(!bBreathe)
		return;

	if(!IsValid(CurrentNode) && !IsValid(AccessibleNode))
	{
		Exit();
	}
	else if(IsCurrentNodeActive())
	{
		if(CurrentNode->bAlwaysUpdate)
		{
			ProcessingNodeInterfaceComponents(CurrentNode, [&DeltaTime](UActorComponent* InComponent)
			{
				if(IActiveNodeInterface::Execute_CanUpdate(InComponent))
				{
					IActiveNodeInterface::Execute_UpdateNode(InComponent, DeltaTime);
				}
			});
			
			if(CurrentNode->CanUpdate())
			{
				CurrentNode->Update(DeltaTime);
			}

			if(CurrentNode->K2_CanUpdate())
			{
				CurrentNode->K2_Update(DeltaTime);
			}
		}
	}
}

bool UActiveNodeSubsystem::IsTickable() const
{
	return Super::IsTickable() && UActiveNodeSettings::Get()->bBlockUpdate;
}

AActiveNode* UActiveNodeSubsystem::GetCurrentActiveNode() const
{
	return CurrentNode;
}

AActiveNode* UActiveNodeSubsystem::ChangeActiveNodeTo(const UObject* WorldContextObject, FGameplayTag InTag, bool& bSucceed, const TSubclassOf<AActiveNode> InClass, bool bReInit)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	AActiveNode* ChangeNode = ThisClass::Get(World)->ChangeNode(InTag, bReInit, bSucceed);
	if(ChangeNode && ChangeNode->IsA(InClass))
	{
		return ChangeNode;
	}
	return nullptr;
}

AActiveNode* UActiveNodeSubsystem::FindActiveNode(const UObject* WorldContextObject, FGameplayTag InTag, const TSubclassOf<AActiveNode> InClass)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	
	if(AActiveNode* FoundNode = ThisClass::Get(World)->FindActiveNode(InTag))
	{
		if(FoundNode->IsA(InClass))
		{
			return FoundNode;
		}
	}
	
	return nullptr;
}

AActiveNode* UActiveNodeSubsystem::FindActiveNode(const FGameplayTag& InTag)
{
	if(CheckTag(InTag))
	{
		return NodeMappings.Contains(InTag) ? NodeMappings[InTag] : nullptr;
	}

	return nullptr;
}

AActiveNode* UActiveNodeSubsystem::Entry(bool& bSucceed, const FGameplayTag& InTag)
{
	bSucceed = false;
	FGameplayTag LoginTag = InTag;

	if(!LoginTag.IsValid())
	{
		LoginTag = UActiveNodeSettings::Get()->DefaultNodeTag;
	}

#if WITH_EDITOR
	// 没有合适 LoginTag , 如果是 PIE, 简单处理一下.
	if(!LoginTag.IsValid())
	{
		TArray<FGameplayTag> NodeTags;
		NodeMappings.GetKeys(NodeTags);
		if(!NodeTags.IsEmpty())
		{
			LoginTag = NodeTags[0];
			UE_LOG(LogActiveNodeSystem, Error, TEXT("There is no valid default active node tag, please check the default/override active node configuration"));
			UE_LOG(LogActiveNodeSystem, Warning, TEXT("Enter the nearest reachable active point '%s', please repair the configuration in time."), *LoginTag.ToString())
		}
	}
#endif

	if(!LoginTag.IsValid())
	{
		ensureMsgf(false, TEXT("Try to enter the active point, but there are no active points available"));
		return nullptr;
	}

	AActiveNode* FoundNode = FindActiveNode(LoginTag);
	
	if(ensureMsgf(IsValid(FoundNode), TEXT("Entry active node faild. not found '%s' node"), *LoginTag.ToString()))
	{
		if(LoginNode(FoundNode))
		{
			OnEntryActiveNodeSystem.Broadcast();
			bSucceed = true;
			return FoundNode;
		}
	}
	
	return nullptr;
}

void UActiveNodeSubsystem::Exit()
{
	if(IsValid(CurrentNode))
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
	if(ensureMsgf(!InNode->bActive, TEXT("Attempt to initialize the node '%s'"), *InNode->NodeTag.ToString()))
	{
		// 对于没有初始化的节点强制该节点进行初始化操作.
		if(bReInit || !InNode->bInitialized)
		{
			InNode->bInitialized = false;
			
			// 处理这个节点所有组件的初始化接口事件.
			ProcessingNodeInterfaceComponents(InNode, [](UActorComponent* InComponent)
            {
            	IActiveNodeInterface::Execute_InitNode(InComponent);
            });
			
            InNode->Init();
			InNode->K2_Init();
			InNode->bInitialized = true;
            InNode->OnNodeInit.Broadcast(InNode);
		}
	}
}

bool UActiveNodeSubsystem::LoginNode(AActiveNode* InNode, bool bReInit)
{
	if(!ensureMsgf(InNode, (TEXT("Login failed, there are no valid login node"))))
		return false;

	InitNode(InNode, bReInit);
	
	// 处理这个节点所有组件的登录接口事件.
	ProcessingNodeInterfaceComponents(InNode, [](UActorComponent* InComponent)
	{
		IActiveNodeInterface::Execute_LoginNode(InComponent);
	});

	CurrentNode = InNode;
	InNode->Login();
	InNode->K2_Login();
	InNode->OnNodeLogin.Broadcast(InNode);
	InNode->bActive = true;
	return true;
}

void UActiveNodeSubsystem::LogoutNode()
{
	ensure(IsValid(CurrentNode));
	
	// 先让这个节点失去活跃, 不再检查它的更新操作.
	CurrentNode->bActive = false;
		
	// 处理这个节点所有组件的登出接口事件.
	ProcessingNodeInterfaceComponents(CurrentNode, [](UActorComponent* InComponent)
	{
		IActiveNodeInterface::Execute_LogoutNode(InComponent);
	});

	CurrentNode->Logout();
	CurrentNode->K2_Logout();
	CurrentNode->OnNodeLogout.Broadcast(CurrentNode);
	CurrentNode = nullptr;
}

AActiveNode* UActiveNodeSubsystem::ChangeNode(const FGameplayTag& InTag, bool bReInit, bool& bSucceed)
{
	bSucceed = false;
	
	if(!CheckTag(InTag))
	{
		bSucceed = false;
		return nullptr;
	}
	
	// 如果当前没有可用的活跃点, 那么尝试进入这个指定 Tag 的活跃点.
	if(!IsValid(CurrentNode))
	{
		UE_LOG(LogActiveNodeSystem, Log, TEXT("There is no active node at the moment, go directly to the '%s' node"), *InTag.ToString())
		return Entry(bSucceed, InTag);
	}

	AActiveNode* ChangeNode = FindActiveNode(InTag);
	
	if(!ensureMsgf(ChangeNode, TEXT("Change active node faild. not found '%s' node"), *InTag.ToString()))
	{
		return nullptr;
	}

	// 这是一个可达的目标节点, 确保执行 LogoutNode 不会进行完全登出(Exit).
	AccessibleNode = ChangeNode;
	
	// 处理即将切换的节点所有组件的预切换接口事件.
	ProcessingNodeInterfaceComponents(ChangeNode, [this](UActorComponent* Component)
	{
		IActiveNodeInterface::Execute_PreChangeNode(Component, CurrentNode);
	});

	ChangeNode->PreChanged(ChangeNode);
	ChangeNode->K2_PreChanged(ChangeNode);
	ChangeNode->OnNodePreChanged.Broadcast(ChangeNode, CurrentNode);
	
	// 登出当前的节点.
	LogoutNode();

	// 登录目标节点.
	if(LoginNode(ChangeNode, bReInit))
	{
		// 处理即将切换的节点所有组件的预切换接口事件.
		ProcessingNodeInterfaceComponents(ChangeNode, [](UActorComponent* Component)
		{
			IActiveNodeInterface::Execute_PostChangeNode(Component);
		});

		ChangeNode->PostChanged();
		ChangeNode->K2_PostChanged();
		ChangeNode->OnNodePostChanged.Broadcast(ChangeNode);
		bSucceed = true;
		return ChangeNode;
	}

	AccessibleNode = nullptr;
	return nullptr;
}

void UActiveNodeSubsystem::ReLogin(const UObject* WorldContextObject, bool bReInit)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	ThisClass::Get(World)->ReLoginNode(bReInit);
}

void UActiveNodeSubsystem::ReLoginNode(bool bReInit)
{
	if(IsValid(CurrentNode))
	{
		AccessibleNode = CurrentNode;
		
		LogoutNode();

		// 永不失败!
		check(LoginNode(AccessibleNode, bReInit));

		// 处理这个节点所有组件的重新登录接口事件.
		ProcessingNodeInterfaceComponents(CurrentNode, [](UActorComponent* InComponent)
		{
			IActiveNodeInterface::Execute_ReLoginNode(InComponent);
		});

		CurrentNode->ReLogin();
		CurrentNode->K2_ReLogin();
		CurrentNode->OnNodeReLogin.Broadcast(CurrentNode);

		AccessibleNode = nullptr;
	}
}

void UActiveNodeSubsystem::ProcessingNodeInterfaceComponents(const AActiveNode* InNode, const TFunctionRef<void(UActorComponent* InComponent)>& InterfaceCall)
{
	TArray<UActorComponent*> Components = InNode->GetComponentsByInterface(UActiveNodeInterface::StaticClass());
	
	for(const auto Component : Components)
	{
		if(Component->IsRegistered() && Component->IsActive())
		{
			InterfaceCall(Component);
		}
	}
}

bool UActiveNodeSubsystem::Entry(const FGameplayTag& InTag)
{
	bool Result = false;
	Entry(Result, InTag);
	return Result;
}

bool UActiveNodeSubsystem::CheckTag(const FGameplayTag& InTag)
{
	if(!InTag.IsValid() || !InTag.MatchesTag(TAG_ActiveNode))
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