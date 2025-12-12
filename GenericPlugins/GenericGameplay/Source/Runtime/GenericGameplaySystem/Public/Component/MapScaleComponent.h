#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MapScaleComponent.generated.h"


UCLASS(ClassGroup=(GenericFramework), meta=(BlueprintSpawnableComponent))
class GENERICGAMEPLAYSYSTEM_API UMapScaleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void DrawMapScaleUnits(AHUD* InHUD, const int32 SizeX, const int32 SizeY); // 调用该函数必须要在AHUD::ReceiveDrawHUD里面
	static FString UnrealUnitsToSiUnits(float UnrealUnits); // 单位换算

	// 手动微调参数
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManualMatchingAlpha = 7.5f;

	// 手动设置地面高度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManualAbsoluteWorldHeight = 0.0f;
};
