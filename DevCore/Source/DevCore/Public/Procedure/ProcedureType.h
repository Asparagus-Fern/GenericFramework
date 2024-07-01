#pragma once

#include "NativeGameplayTags.h"
#include "ProcedureInterface.h"

class UCoreManager;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Procedure);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureLoading);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureMainMenu);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedurePlay);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedurePause);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureExit);

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameplayProcedure : uint8
{
	None,
	Loading UMETA(DisplayName="加载"),
	MainMenu UMETA(DisplayName="主菜单"),
	Play UMETA(DisplayName="游玩"),
	Exit UMETA(DisplayName="退出")
};

/**
 * 流程处理句柄
 */
struct DEVCORE_API FProcedureInterfaceHandle
{
public:
	FProcedureInterfaceHandle();
	FProcedureInterfaceHandle(IProcedureInterface* InInterface, bool InTargetActiveState);
	

public:
	bool operator==(const FProcedureInterfaceHandle& Other) const
	{
		return Interface == Other.Interface;
	}

	bool operator==(const IProcedureInterface* OtherInterface) const
	{
		return Interface == OtherInterface;
	}

public:
	/* 需要进行处理的类对象 */
	IProcedureInterface* Interface;

	/* 期望的激活状态 */
	bool bTargetActiveState;
};
