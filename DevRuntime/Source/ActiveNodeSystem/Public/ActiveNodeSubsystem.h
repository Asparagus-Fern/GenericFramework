// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNode.h"
#include "ActiveNodeInterface.h"
#include "NativeGameplayTags.h"
#include "Subsystems/WorldSubsystem.h"
#include "ActiveNodeSubsystem.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogActiveNodeSystem, Log, All);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ActiveNode);

class AActiveNode;

/**
 * 活跃点管理子系统.
 */
UCLASS()
class ACTIVENODESYSTEM_API UActiveNodeSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UActiveNodeSubsystem();

	static ThisClass* Get(const UWorld* InWorld);

protected:
	// 当前所在的活跃节点
	UPROPERTY(Transient)
	TObjectPtr<AActiveNode> CurrentNode;

	// 临时容器, 用于切换活跃点, 确保当前还有存活的活跃点
	UPROPERTY(Transient)
	TObjectPtr<AActiveNode> AccessibleNode;

	// 节点映射.
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<AActiveNode>> NodeMappings;

public:
	// Begin USubsystem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem Interface.

	// Begin UWorldSubsystem Interface.
	virtual void PostInitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void OnWorldComponentsUpdated(UWorld& World) override;
	virtual void UpdateStreamingState() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	// End UWorldSubsystem Interface.

	// Begin TickableGameObject Interface.
	virtual TStatId GetStatId() const override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	// End TickableWorldSubsystem Interface.

	// 获取当前所在的活跃点.
	UFUNCTION(BlueprintPure, Category = ActiveNode)
	AActiveNode* GetCurrentActiveNode() const;

	/**
	 * 尝试切换至指定 Tag 的活跃点.
	 * @param WorldContextObject
	 * @param InTag 活跃节点标识符.
	 * @param bSucceed 是否成功.
	 * @param InClass 要转换的具体类型.
	 * @param bReInit 重新执行初始化
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", InClass = "/Script/ActiveNode.ActiveNode", DeterminesOutputType = "InClass", ReInit = "true", AdvancedDisplay = "4"), Category = ActiveNode)
	static AActiveNode* ChangeActiveNodeTo(const UObject* WorldContextObject, UPARAM(meta = (Categories = "ActiveNode")) FGameplayTag InTag, bool& bSucceed, const TSubclassOf<AActiveNode> InClass, bool bReInit);

	/**
	 * 查找活跃点. 这个方法暴露给蓝图和设计理念上有所冲突.
	 * @param WorldContextObject 
	 * @param InTag 活跃节点标识符.
	 * @param InClass 要转换的具体类型.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", InClass = "/Script/ActiveNode.ActiveNode", DeterminesOutputType = "InClass"), Category = ActiveNode)
	static AActiveNode* FindActiveNode(const UObject* WorldContextObject, UPARAM(meta = (Categories = "ActiveNode")) FGameplayTag InTag, const TSubclassOf<AActiveNode> InClass);

	AActiveNode* FindActiveNode(const FGameplayTag& InTag);

	template <class TClass>
	TClass* FindActiveNode(const FGameplayTag& InTag)
	{
		if (AActiveNode* FoundNode = FindActiveNode(InTag))
		{
			return Cast<TClass>(FoundNode);
		}
		return nullptr;
	}

	// 切换至指定 Tag 的活跃点, 如果活跃点存在.
	AActiveNode* ChangeNode(const FGameplayTag& InTag, bool bReInit, bool& bSucceed);

	template <class TClass>
	TClass* ChangeNode(const FGameplayTag& InTag, bool bReInit)
	{
		bool Result;
		return Cast<TClass>(ChangeNode(InTag, bReInit, Result));
	}

	/**
	 * 重新登录当前的活跃点, 如果活跃点存在的话.
	 * @param WorldContextObject
	 * @param bReInit 重新执行初始化.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ActiveNode)
	static void ReLogin(const UObject* WorldContextObject, bool bReInit = true);

	// 重新登录当前的活跃节点. 如果节点存在的话.
	void ReLoginNode(bool bReInit = true);

	// 通知, 在首次进入活跃点时触发.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEntryActiveNodeSystem);

	UPROPERTY(BlueprintAssignable)
	FOnEntryActiveNodeSystem OnEntryActiveNodeSystem;

	// 通知, 在完全退出活跃点时触发.
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeaveActiveNodeSystem);

	UPROPERTY(BlueprintAssignable)
	FOnLeaveActiveNodeSystem OnLeaveActiveNodeSystem;

protected:
	/* 活跃点 -> 从无到有的开始 */
	virtual AActiveNode* Entry(bool& bSucceed, const FGameplayTag& InTag);

	/* 完全退出 */
	virtual void Exit();

	/**
	 * @param InNode 初始化指定节点, 指定的节点不能是处于活跃中的.
	 * @param bReInit 对于已经初始化的节点再次执行初始化操作.
	 */
	void InitNode(AActiveNode* InNode, bool bReInit = false);

	// 登录节点, 如果当前存在未登出的节点. 将不会执行登录.
	bool LoginNode(AActiveNode* InNode, bool bReInit = true);

	// 登出当前的节点
	void LogoutNode();

	// 指定节点的组件接口事务处理.
	void ProcessingNodeInterfaceComponents(const AActiveNode* InNode, const TFunctionRef<void(UActorComponent* InComponent)>& InterfaceCall);

private:
	uint8 bBreathe : 1;
	bool Entry(const FGameplayTag& InTag = FGameplayTag());
	bool CheckTag(const FGameplayTag& InTag);
	bool IsCurrentNodeActive() const;
};
