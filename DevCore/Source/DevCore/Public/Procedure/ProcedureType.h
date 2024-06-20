#pragma once

class UCoreManager;

/**
 * 
 */
struct FManagerOrder
{
public:
	FManagerOrder(int32 InOrder);
	bool operator==(const int32 InOrder) const { return Order == InOrder; }

public:
	int32 Order;
	TArray<UCoreManager*> Managers;
};

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameplayProcedure : uint8
{
	None,
	GameLoading UMETA(DisplayName="加载"),
	MainMenu UMETA(DisplayName="主菜单"),
	Play UMETA(DisplayName="游玩"),
	Pause UMETA(DisplayName="暂停"),
	Exit UMETA(DisplayName="退出")
};
