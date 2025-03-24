// Copyright ChenTaiye 2025. All Rights Reserved.


#include "HUD/DevHUD.h"

#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

ADevHUD::ADevHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ADevHUD::DrawHUD()
{
	Super::DrawHUD();
	// DrawMapScale();
}

void ADevHUD::DrawMapScale()
{
	// if (USceneManager* SceneManager = GetManager<USceneManager>(this))
	// {
	// 	APlayerController* PC = GetOwningPlayerController();
	// 	APlayerCameraManager* PlayerCameraManager = PC->PlayerCameraManager;
	// 	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	// 	UGameViewportClient* GameViewportClient = LocalPlayer->ViewportClient;
	//
	// 	float DPIScale = LocalPlayer->ViewportClient->GetDPIScale();
	// 	float CameraLocationZ = PlayerCameraManager->GetCameraLocation().Z;
	// 	float CameraRotationP = PlayerCameraManager->GetCameraRotation().Pitch;
	// 	float CameraHeight = PlayerCameraManager->GetCameraLocation().Z - SceneManager->GetWorldElevationOriginHeight();
	//
	// 	{
	// 		const float SizeX = static_cast<float>(GameViewportClient->Viewport->GetSizeXY().X);
	// 		const float UnitsPerPixel = 100 / (SceneManager->GetWorldElevationOriginHeight() / CameraLocationZ * (SizeX));
	//
	// 		static const int32 ApproxTargetMarkerWidthPx = 100;
	// 		const float SegmentWidthUnits = UnitsPerPixel > 0 ? FMath::Pow(10.f, FMath::RoundToFloat(FMath::LogX(10.f, UnitsPerPixel * ApproxTargetMarkerWidthPx))) : 0.f;
	//
	// 		const FString DisplayText = UBPFunctions_Scene::GetUnrealUnitsFormatString(SegmentWidthUnits);
	//
	// 		UFont* Font = GEngine->GetTinyFont();
	// 		int32 TextWidth, TextHeight;
	// 		StringSize(Font, TextWidth, TextHeight, *DisplayText);
	//
	// 		const FIntPoint StartPoint(Canvas->SizeX / DPIScale - 30, Canvas->SizeY / DPIScale - 30);
	// 		const FIntPoint EndPoint = StartPoint - (UnitsPerPixel != 0 ? FIntPoint(SegmentWidthUnits / UnitsPerPixel, 0) : FIntPoint(0, 0));
	//
	// 		// FLinearColor HSVBackground = Canvas->SceneView->BackgroundColor.LinearRGBToHSV().CopyWithNewOpacity(1.f);
	// 		// const int32 Sign = (0.5f - HSVBackground.B) / FMath::Abs(HSVBackground.B - 0.5f);
	// 		// HSVBackground.B = HSVBackground.B + Sign * 0.4f;
	// 		// const FLinearColor SegmentColor = HSVBackground.HSVToLinearRGB();
	// 		const FLinearColor SegmentColor = FLinearColor(FColor(255, 255, 255, 255));
	//
	// 		const FIntPoint VerticalTickOffset(0, -3);
	//
	// 		DrawLine(StartPoint.X, StartPoint.Y, (StartPoint + VerticalTickOffset).X, (StartPoint + VerticalTickOffset).Y, SegmentColor, 1.0);
	// 		DrawLine(StartPoint.X, StartPoint.Y, EndPoint.X, EndPoint.Y, SegmentColor, 1.0);
	// 		DrawLine(EndPoint.X, EndPoint.Y, (EndPoint + VerticalTickOffset).X, (EndPoint + VerticalTickOffset).Y, SegmentColor, 1.0);
	// 		DrawText(DisplayText, SegmentColor, (EndPoint + FIntPoint(TextWidth - 15, -TextHeight)).X, (EndPoint + FIntPoint(TextWidth - 15, -TextHeight)).Y, Font);
	// 	}
	// }
}
