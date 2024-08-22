// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
UCLASS(Blueprintable, HideCategories = (Physics, Cooking), ShowCategories=(Transformation, Input, DataLayers))
class ACTIVENODESYSTEM_API AActiveNode : public AInfo
{
	GENERATED_UCLASS_BODY()
	friend class UActiveNodeSubsystem;

	// 该活跃节点的 Tag 标志.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "ActiveNode"), Category = ActiveNode)
	FGameplayTag NodeTag;

	// 是活跃中的节点
	UFUNCTION(BlueprintPure, Category = ActiveNode)
	bool IsActivationNode() const;

protected:
	// from cpp Interface.
	virtual void Init()
	{
	}

	virtual void Login()
	{
	}

	virtual void Logout()
	{
	}

	virtual void ReLogin()
	{
	}

	virtual void PreChanged(const AActiveNode* FromNode)
	{
	}

	virtual void PostChanged()
	{
	}

	virtual bool CanUpdate() { return true; }

	virtual void Update(float Delta)
	{
	}


	/* ---------------------------------------- FROM BLUEPRINT INTERFACE ---------------------------------------- */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInit"), Category = NodeInterface)
	void K2_Init();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnLogin"), Category = NodeInterface)
	void K2_Login();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnLogout"), Category = NodeInterface)
	void K2_Logout();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnReLogin"), Category = NodeInterface)
	void K2_ReLogin();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPreChanged"), Category = NodeInterface)
	void K2_PreChanged(const AActiveNode* FromNode);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPostChanged"), Category = NodeInterface)
	void K2_PostChanged();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "CanUpdate"), Category = NodeInterface)
	bool K2_CanUpdate();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnUpdate"), Category = NodeInterface)
	void K2_Update(float Delta);

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
	/* 总是更新, 如果取消勾选, 在这个节点处于活跃时将不在更新, 将影响 ComponentUpdate */
	UPROPERTY(EditDefaultsOnly, Category = ActiveNode)
	uint8 bAlwaysUpdate : 1;

	/* 总是更新组件, 如果取消勾选, 在这个节点处于活跃时, 该节点所有的 IActiveNodeInterface 接口组件都将不在进行更新 */
	UPROPERTY(EditDefaultsOnly, Category = ActiveNode)
	uint8 bComponentUpdate : 1;

	// 内部标记, 表示这个活跃点已被初始化.
	uint8 bInitialized : 1;

	// 内部标记, 表示这个活跃点已被激活
	uint8 bActive : 1;
};
