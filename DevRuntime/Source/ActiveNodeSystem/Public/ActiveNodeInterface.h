// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActiveNodeInterface.generated.h"

class AActiveNode;

// This class does not need to be modified.
UINTERFACE()
class UActiveNodeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 活跃点接口
 */
class ACTIVENODESYSTEM_API IActiveNodeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 登记节点, 在这个节点被节点世界子系统登记时调用. 在 node PostComponentInit 阶段 之前
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void RegisterNode();

	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void UnRegisterNode();

	// 初始化节点
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void InitNode();

	// 登录至该节点时调用.
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void LoginNode();

	// 重新登录.
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void ReLoginNode();

	// 登出节点
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void LogoutNode();

	// 节点能否更新.
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	bool CanUpdate();

	// 更新节点.
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void UpdateNode(float DeltaTime);

	// 准备从上一个活跃点切换至此活跃点, 在该活跃点初始化之前调用.
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void PreChangeNode(const AActiveNode* FromNode);

	// 准备从上一个活跃点切换至此活跃点, 在该活跃点初始化之后调用.
	UFUNCTION(BlueprintNativeEvent, Category = ActiveNodeInterface)
	void PostChangeNode();
};
