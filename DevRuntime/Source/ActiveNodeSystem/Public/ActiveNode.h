// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNodeInterface.h"
#include "GameplayTagContainer.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "GameFramework/Info.h"
#include "ActiveNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNodePreChanged, AActiveNode*, Node, AActiveNode*, FromNode);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeInit, AActiveNode*, Node);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodePostChanged, AActiveNode*, Node);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeLogin, AActiveNode*, Node);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeLogout, AActiveNode*, Node);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeReLogin, AActiveNode*, Node);

/**
 * 活跃点.
 */
UCLASS(Blueprintable)
class ACTIVENODESYSTEM_API AActiveNode : public AActor, public IActiveNodeInterface
{
	GENERATED_UCLASS_BODY()

public:
	// Begin AActor Interface.
#if WITH_EDITOR
	virtual bool CanChangeIsSpatiallyLoadedFlag() const override { return false; }
#endif

	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor Interface.

	// 该活跃节点的 Tag 标志.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "ActiveNode"), Category = ActiveNode)
	FGameplayTag NodeTag;

	// 登录到这个节点
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category = ActiveNode)
	bool Login(const UObject* WorldContextObject, bool bReInit);

	// 重新登录.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ActiveNode)
	void ReLogin(const UObject* WorldContextObject, bool bReInit);

	/* ---------------------------------------- FROM MULTICAST DELEGATE ---------------------------------------- */
	// 准备切换至该活跃点, 从一个正确的活跃点执行切换至该活跃点时触发. (在处理初始化和登录之前)
	UPROPERTY(BlueprintAssignable)
	FOnNodePreChanged OnNodePreChanged;

	// 当该活跃点被初始化时调用 (包括可选的 ReInit 时.)
	UPROPERTY(BlueprintAssignable)
	;
	FOnNodeInit OnNodeInit;

	// 当登录至该活跃点时触发.
	UPROPERTY(BlueprintAssignable)
	FOnNodeLogin OnNodeLogin;

	// 完全切换至该活跃点, 从一个正确的活跃点执行切换至该活跃点时触发. (在处理完登录之后)
	UPROPERTY(BlueprintAssignable)
	FOnNodePostChanged OnNodePostChanged;

	// 当执行登出该活跃点时触发.
	UPROPERTY(BlueprintAssignable)
	FOnNodeLogout OnNodeLogout;

	// 当执行重新登录时触发.
	UPROPERTY(BlueprintAssignable)
	FOnNodeReLogin OnNodeReLogin;

private:
	/* 总是更新, 如果取消勾选, 在这个节点处于活跃时将不在更新, 这个操作会同步影响至 ComponentUpdate */
	UPROPERTY(EditDefaultsOnly, Category = ActiveNode)
	uint8 bAlwaysUpdate : 1;

	/* 总是更新组件, 如果取消勾选, 在这个节点处于活跃时, 该节点所有的 UActiveNodeComponent 组件都将不在进行更新 */
	UPROPERTY(EditDefaultsOnly, Category = ActiveNode)
	uint8 bComponentUpdate : 1;

	// 内部标记, 表示这个活跃点已被初始化.
	uint8 bInitialized : 1;

	// 内部标记, 表示这个活跃点已被激活
	uint8 bActive : 1;

	friend class UActiveNodeSubsystem;
};
