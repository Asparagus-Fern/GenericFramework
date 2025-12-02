// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Actor/CompassActor.h"

#include "GameplayType.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Type/DebugType.h"

ACompassActor::ACompassActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	SetupComponent(ArrowComponentN,TEXT("North"), TextRenderN,TEXT("TextN"), 0.f, FColor(255, 0, 0, 255), "N");
	SetupComponent(ArrowComponentS,TEXT("South"), TextRenderS,TEXT("TextS"), 180.f, FColor(0, 0, 255, 255), "S");
	SetupComponent(ArrowComponentE,TEXT("East"), TextRenderE,TEXT("TextE"), 90.f, FColor(255, 0, 0, 255), "E");
	SetupComponent(ArrowComponentW,TEXT("West"), TextRenderW,TEXT("TextW"), 270.f, FColor(0, 0, 255, 255), "W");
}

void ACompassActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACompassActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SceneComponent->SetRelativeRotation(FRotator(0.f, Angle, 0.f));

	GenericLOG(GenericLogGameplay, Log, TEXT("Direction : %s"), *GetDirectionNorth().ToString())
}

bool ACompassActor::GetPlayerForwardAngle(const UObject* WorldContextObject, int32 PlayerIndex, float& OutAngle)
{
	if (ACompassActor* CompassActor = Cast<ACompassActor>(UGameplayStatics::GetActorOfClass(WorldContextObject, ACompassActor::StaticClass())))
	{
		const FVector WorldNorthDirection = CompassActor->GetDirectionNorth();
		const FVector WorldEastDirection = CompassActor->GetDirectionEast();

		if (const APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(WorldContextObject, PlayerIndex))
		{
			const FVector LookForward = PlayerCameraManager->GetActorForwardVector().GetSafeNormal2D();

			float DegreesNorth = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(WorldNorthDirection, LookForward)));
			const float DegreesEast = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(WorldEastDirection, LookForward)));

			if (DegreesEast > 90.f)
			{
				DegreesNorth = -DegreesNorth;
			}

			OutAngle = DegreesNorth;
			return true;
		}
	}

	return false;
}

void ACompassActor::SetupComponent(UArrowComponent*& InArrow, FName InArrowName, UTextRenderComponent*& InTextRender, FName InTextRenderName, float InArrowYaw, FColor InArrowColor, FString InText)
{
	InArrow = CreateDefaultSubobject<UArrowComponent>(InArrowName);
	InArrow->SetupAttachment(SceneComponent);
	InArrow->SetRelativeRotation(FRotator(0.f, InArrowYaw, 0.f));
	InArrow->ArrowColor = InArrowColor;

	InTextRender = CreateDefaultSubobject<UTextRenderComponent>(InTextRenderName);
	InTextRender->SetupAttachment(InArrow);
	InTextRender->SetRelativeLocation(FVector(InArrow->ArrowLength, 0.f, 0.f));
	InTextRender->SetRelativeRotation(FRotator(90.f, 180.f, 0.f));
	InTextRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	InTextRender->Text = FText::FromString(InText);
	InTextRender->SetHiddenInGame(true);
}

FVector ACompassActor::GetDirectionNorth() const
{
	return ArrowComponentN->GetForwardVector().GetSafeNormal2D();
}

FVector ACompassActor::GetDirectionEast() const
{
	return ArrowComponentN->GetRightVector().GetSafeNormal2D();
}
