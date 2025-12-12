#include "Component/MapScaleComponent.h"

#include "CanvasTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/HUD.h"

void UMapScaleComponent::DrawMapScaleUnits(AHUD* InHUD, const int32 SizeX, const int32 SizeY)
{
	if (!IsValid(InHUD))
	{
		return;
	}

	APlayerController* PC = InHUD->GetOwningPlayerController();
	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	AHUD* HUD = InHUD;

	float DPIScale = LocalPlayer->ViewportClient->GetDPIScale();

	UActorComponent* ActorComponent = PC->GetPawn()->GetComponentByClass(UCameraComponent::StaticClass());
	if (!ActorComponent)
	{
		return;
	}
	UCameraComponent* CameraComponent = Cast<UCameraComponent>(ActorComponent);
	if (!CameraComponent)
	{
		return;
	}
	double PawnHeight = CameraComponent->GetComponentLocation().Z - ManualAbsoluteWorldHeight;

	const float UnitsPerPixel = (PawnHeight / 100.0f) / ManualMatchingAlpha * DPIScale;

	// Find the closest power of ten to our target width
	static const int32 ApproxTargetMarkerWidthPx = 100;
	const float SegmentWidthUnits = UnitsPerPixel > 0 ? FMath::Pow(10.f, FMath::RoundToFloat(FMath::LogX(10.f, UnitsPerPixel * ApproxTargetMarkerWidthPx))) : 0.f;

	const FString DisplayText = UnrealUnitsToSiUnits(SegmentWidthUnits);

	UFont* Font = GEngine->GetTinyFont();
	int32 TextWidth, TextHeight;
	StringSize(Font, TextWidth, TextHeight, *DisplayText);

	// Origin is the bottom right of the scale
	const FIntPoint StartPoint(SizeX / DPIScale - 30, SizeY / DPIScale - 30);
	const FIntPoint EndPoint = StartPoint - (UnitsPerPixel != 0 ? FIntPoint(SegmentWidthUnits / UnitsPerPixel, 0) : FIntPoint(0, 0));

	const FLinearColor SegmentColor = FLinearColor(FColor(255, 255, 255, 255));
	const FIntPoint VerticalTickOffset(0, -3);

	HUD->DrawLine(StartPoint.X, StartPoint.Y, (StartPoint + VerticalTickOffset).X, (StartPoint + VerticalTickOffset).Y, SegmentColor, 1.0);
	HUD->DrawLine(StartPoint.X, StartPoint.Y, EndPoint.X, EndPoint.Y, SegmentColor, 1.0);
	HUD->DrawLine(EndPoint.X, EndPoint.Y, (EndPoint + VerticalTickOffset).X, (EndPoint + VerticalTickOffset).Y, SegmentColor, 1.0);
	HUD->DrawText(DisplayText, SegmentColor, (EndPoint + FIntPoint(TextWidth - 15, -TextHeight)).X, (EndPoint + FIntPoint(TextWidth - 15, -TextHeight)).Y, Font);
}

FString UMapScaleComponent::UnrealUnitsToSiUnits(float UnrealUnits)
{
	// Put it in mm to start off with
	UnrealUnits *= 10.f;

	const int32 OrderOfMagnitude = UnrealUnits > 0 ? FMath::TruncToInt(FMath::LogX(10.0f, UnrealUnits)) : 0;

	// Get an exponent applied to anything >= 1,000,000,000mm (1000km)
	const int32 Exponent = (OrderOfMagnitude - 6) / 3;
	const FString ExponentString = Exponent > 0 ? FString::Printf(TEXT("e+%d"), Exponent * 3) : TEXT("");

	float ScaledNumber = UnrealUnits;

	// Factor the order of magnitude into thousands and clamp it to km
	const int32 OrderOfThousands = OrderOfMagnitude / 3;
	if (OrderOfThousands != 0)
	{
		// Scale units to m or km (with the order of magnitude in 1000s)
		ScaledNumber /= FMath::Pow(1000.f, OrderOfThousands);
	}

	// Round to 2 S.F.
	const TCHAR* Approximation = TEXT("");
	{
		const int32 ScaledOrder = OrderOfMagnitude % (FMath::Max(OrderOfThousands, 1) * 3);
		const float RoundingDivisor = FMath::Pow(10.f, ScaledOrder) / 10.f;
		const int32 Rounded = FMath::TruncToInt(ScaledNumber / RoundingDivisor) * RoundingDivisor;
		if (ScaledNumber - Rounded > KINDA_SMALL_NUMBER)
		{
			ScaledNumber = Rounded;
			Approximation = TEXT("~");
		}
	}

	if (OrderOfMagnitude <= 2)
	{
		// Always show cm not mm
		ScaledNumber /= 10;
	}

	static const TCHAR* UnitText[] = {TEXT("cm"), TEXT("m"), TEXT("km")};
	if (FMath::Fmod(ScaledNumber, 1.f) > KINDA_SMALL_NUMBER)
	{
		return FString::Printf(TEXT("%s%.1f%s%s"), Approximation, ScaledNumber, *ExponentString, UnitText[FMath::Min(OrderOfThousands, 2)]);
	}
	else
	{
		return FString::Printf(TEXT("%s%d%s%s"), Approximation, FMath::TruncToInt(ScaledNumber), *ExponentString, UnitText[FMath::Min(OrderOfThousands, 2)]);
	}
}
