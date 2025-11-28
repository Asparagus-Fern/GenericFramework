// Copyright ChenTaiye 2025. All Rights Reserved.

#include "SceneSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Compass/CompassActor.h"
#include "Type/DebugType.h"
#include "MapScale/MapScaleActor.h"

USceneSubsystem* USceneSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void USceneSubsystem::OnWorldMatchStarting()
{
	Super::OnWorldMatchStarting();

	// CompassActor = Cast<ACompassActor>(UGameplayStatics::GetActorOfClass(this, ACompassActor::StaticClass()));
	// MapScaleActor = Cast<AMapScaleActor>(UGameplayStatics::GetActorOfClass(this, AMapScaleActor::StaticClass()));
}

void USceneSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
	Super::OnWorldBeginTearDown(InWorld);
}

TArray<AActor*> USceneSubsystem::FindActors(const FFindActorHandle& InFindActorHandle, const bool bUpdate)
{
	if (FFoundActorHandle* FoundActorHandle = FoundActorHandles.FindByKey(InFindActorHandle))
	{
		if (bUpdate)
		{
			FoundActorHandle->FoundActors = FindActors(InFindActorHandle);
		}

		return FoundActorHandle->FoundActors;
	}
	else
	{
		FFoundActorHandle* NewFoundActorHandle = new FFoundActorHandle();
		NewFoundActorHandle->FindActorHandle = InFindActorHandle;
		NewFoundActorHandle->FoundActors = FindActors(InFindActorHandle);

		FoundActorHandles.Add(*NewFoundActorHandle);
		return NewFoundActorHandle->FoundActors;
	}
}

TArray<AActor*> USceneSubsystem::FindActors(const FFindActorHandle& InFindActorHandle) const
{
	TArray<AActor*> Actors;

	switch (InFindActorHandle.FindActorMethod)
	{
	case EFindActorMethod::Class:
		UGameplayStatics::GetAllActorsOfClass(this, InFindActorHandle.ActorClass, Actors);
		break;

	case EFindActorMethod::Tag:
		UGameplayStatics::GetAllActorsWithTag(this, InFindActorHandle.ActorTag, Actors);
		break;

	case EFindActorMethod::ClassAndTag:
		UGameplayStatics::GetAllActorsOfClassWithTag(this, InFindActorHandle.ActorClass, InFindActorHandle.ActorTag, Actors);
		break;

	case EFindActorMethod::Interface:
		UGameplayStatics::GetAllActorsWithInterface(this, InFindActorHandle.ActorInterface, Actors);
		break;
	}

	return Actors;
}

float USceneSubsystem::GetPlayerPointToNorthAngle(int32 PlayerIndex) const
{
	if (!IsValid(CompassActor))
	{
		GenericLOG(GenericLogWorld, Log, TEXT("CompassActor Is InValid"))
		return 0.f;
	}

	const FVector WorldNorthDirection = CompassActor->GetDirectionNorth();
	const FVector WorldEastDirection = CompassActor->GetDirectionEast();

	if (const APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, PlayerIndex))
	{
		const FVector LookForward = PlayerCameraManager->GetActorForwardVector().GetSafeNormal2D();

		float DegreesNorth = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(WorldNorthDirection, LookForward)));
		const float DegreesEast = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(WorldEastDirection, LookForward)));

		if (DegreesEast > 90.f)
		{
			DegreesNorth = -DegreesNorth;
		}

		return DegreesNorth;
	}

	return 0.f;
}

float USceneSubsystem::GetWorldElevationOriginHeight() const
{
	if (!IsValid(CompassActor))
	{
		GenericLOG(GenericLogWorld, Log, TEXT("CompassActor Is InValid"))
		return 0.f;
	}

	return CompassActor->GetActorLocation().Z;
}
