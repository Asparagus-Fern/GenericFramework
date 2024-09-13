// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/GameMapUI.h"

#include "BPFunctions/BPFunctions_Math.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widget/GameMapBackground.h"
#include "Widget/GameMapPlayer.h"

void UGameMapUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	Background = SetupBackgroundUI(BackgroundImageBrush);
	Player = SetupPlayerUI(PlayerImageBrush, PlayerForwardImageBrush);
}

void UGameMapUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	switch (Maptype)
	{
	case EMapType::StaticMap:
		Player->SetRenderTranslation(CalculatePlayerSceneLocationToMapLocation(GetPlayerSceneLocation()));
		Player->SetRenderTransformAngle(CalculatePlayerSceneRotationToMapLocation(GetPlayerSceneRotation()));
		break;

	case EMapType::StaticPlayer:
		Background->SetRenderTranslation(CalculatePlayerSceneLocationToMapLocation(GetPlayerSceneLocation()));
		Player->SetRenderTransformAngle(CalculatePlayerSceneRotationToMapLocation(GetPlayerSceneRotation()));
		break;

	default: ;
	}
}

FVector2D UGameMapUI::GetBackgroundSize() const
{
	return BackgroundImageBrush.Size;
}

FVector2D UGameMapUI::GetPlayerSize() const
{
	return PlayerImageBrush.Size;
}

FVector2D UGameMapUI::CalculatePlayerSceneLocationToMapLocation_Implementation(FVector InPlayerSceneLocation)
{
	const FVector2D ConvertSceneLocation = UKismetMathLibrary::GetRotated2D(UKismetMathLibrary::Conv_VectorToVector2D(InPlayerSceneLocation), SceneAngle * -1);
	FVector2D MinMapTranslation = FVector2D::ZeroVector;
	FVector2D MaxMapTranslation = FVector2D::ZeroVector;
	FVector2D PlayerOffset = FVector2D::ZeroVector;

	switch (Maptype)
	{
	case EMapType::StaticMap:
		MaxMapTranslation = GetBackgroundSize();
		PlayerOffset = GetPlayerSize() / 2;
		break;

	case EMapType::StaticPlayer:
		MinMapTranslation = FVector2D::ZeroVector + GetBackgroundSize() / 2;
		MaxMapTranslation = FVector2D::ZeroVector - GetBackgroundSize() / 2;
		break;

	default: ;
	}

	const FVector2D Translation = UBPFunctions_Math::Vector2D_MapRangeClamped(ConvertSceneLocation, FVector2D::ZeroVector, SceneSize, MinMapTranslation, MaxMapTranslation);
	return Translation - PlayerOffset;
}

float UGameMapUI::CalculatePlayerSceneRotationToMapLocation_Implementation(FRotator InPlayerSceneRotation)
{
	return InPlayerSceneRotation.Yaw;
}

FVector UGameMapUI::GetPlayerSceneLocation_Implementation()
{
	return GetOwningPlayerPawn()->GetActorLocation();
}

FRotator UGameMapUI::GetPlayerSceneRotation_Implementation()
{
	return GetOwningPlayerPawn()->GetActorRotation();
}

UGameMapBackground* UGameMapUI::SetupBackgroundUI_Implementation(FImageBrush InBackgroundImageBrush)
{
	return CreateWidget<UGameMapBackground>(this, UGameMapBackground::StaticClass());
}

UGameMapPlayer* UGameMapUI::SetupPlayerUI_Implementation(FImageBrush InPlayerImageBrush, FImageBrush InPlayerForwardImageBrush)
{
	return CreateWidget<UGameMapPlayer>(this, UGameMapPlayer::StaticClass());
}
