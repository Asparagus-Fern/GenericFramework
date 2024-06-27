#pragma once
#include "NativeGameplayTags.h"

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
	Pause UMETA(DisplayName="暂停"),
	Exit UMETA(DisplayName="退出")
};
