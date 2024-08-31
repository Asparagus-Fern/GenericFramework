#pragma once

#include "NativeGameplayTags.h"
#include "ProcedureInterface.h"
#include "ProcedureType.generated.h"

class UProcedureProxy;
class UGameplayProcedure;
class UProcedureObject;
class UCoreManager;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Procedure);

struct DEVCORE_API FProcedureDelegates
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FPocedureProxyDelegate, UProcedureProxy*)
	static FPocedureProxyDelegate OnProxyHandleBegin;
	static FPocedureProxyDelegate OnProxyHandlePause;
	static FPocedureProxyDelegate OnProxyHandleContinue;
	static FPocedureProxyDelegate OnProxyHandleStop;
	static FPocedureProxyDelegate OnProxyHandleFinish;

	/* Param1 is LastGameplayProcedure,Param2 is CurrentGameplayProcedure */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameplayProcedureSwitch, UGameplayProcedure*, UGameplayProcedure*)
	static FOnGameplayProcedureSwitch OnGameplayProcedureSwitch;
};

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
 * 需要被处理的对象
 */
struct DEVCORE_API FProcedureHandle
{
public:
	FProcedureHandle();
	FProcedureHandle(UProcedureObject* InProcedureObject, bool InTargetActiveState, bool InIsAsync = false);

public:
	bool operator==(const FProcedureHandle Other) const
	{
		return ProcedureObject == Other.ProcedureObject;
	}

	bool operator==(const UProcedureObject* OtherProcedureObject) const
	{
		return ProcedureObject == OtherProcedureObject;
	}

public:
	/* 需要进行处理的类对象 */
	UProcedureObject* ProcedureObject;

	/* 期望的激活状态 */
	bool bTargetActiveState;
};

/**
 * 一组需要被处理的对象
 */
struct DEVCORE_API FProcedureHandleGroup
{
public:
	FProcedureHandleGroup();
	FProcedureHandleGroup(const TArray<FProcedureHandle>& InProcedureHandles);
	void CheckHandles();
	bool CanHandle() const { return !ProcedureHandles.IsEmpty(); }

public:
	TArray<FProcedureHandle> ProcedureHandles;

	/* 开始 */
	FSimpleDelegate OnBegin;

	/* 完成 */
	FSimpleDelegate OnFinish;

	/* 暂停 */
	FSimpleDelegate OnPause;

	/* 继续 */
	FSimpleDelegate OnContinue;

	/* 停止 */
	FSimpleDelegate OnStop;
};
