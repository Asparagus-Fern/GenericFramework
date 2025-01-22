// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMapType.h"
#include "SlateType.h"
#include "Base/UserWidgetBase.h"
#include "GameMapUI.generated.h"

class UGameMapPlayer;
class UGameMapBackground;

/**
 * 
 */
UCLASS()
class GAMEMAPSYSTEM_API UGameMapUI : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EMapType Maptype = EMapType::StaticMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FImageBrush BackgroundImageBrush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FImageBrush PlayerImageBrush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FImageBrush PlayerForwardImageBrush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SceneAngle = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D SceneOriginLocation = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D SceneSize = FVector2D::ZeroVector;

protected:
	UPROPERTY(BlueprintReadOnly)
	UGameMapBackground* Background;

	UPROPERTY(BlueprintReadOnly)
	UGameMapPlayer* Player;

public:
	UFUNCTION(BlueprintPure)
	FVector2D GetBackgroundSize() const;

	UFUNCTION(BlueprintPure)
	FVector2D GetPlayerSize() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FVector GetPlayerSceneLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FRotator GetPlayerSceneRotation();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FVector2D CalculatePlayerSceneLocationToMapLocation(FVector InPlayerSceneLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	float CalculatePlayerSceneRotationToMapLocation(FRotator InPlayerSceneRotation);

protected:
	UFUNCTION(BlueprintNativeEvent)
	UGameMapBackground* SetupBackgroundUI(FImageBrush InBackgroundImageBrush);

	UFUNCTION(BlueprintNativeEvent)
	UGameMapPlayer* SetupPlayerUI(FImageBrush InPlayerImageBrush, FImageBrush InPlayerForwardImageBrush);
};
