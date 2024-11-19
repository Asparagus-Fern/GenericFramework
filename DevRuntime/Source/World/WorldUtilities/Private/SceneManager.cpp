// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneManager.h"

#include "Kismet/GameplayStatics.h"
#include "SceneManagerSetting.h"
#include "Compass/CompassActor.h"
#include "MapScale/MapScaleActor.h"

bool USceneManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && USceneManagerSetting::Get()->GetEnableManager();
}

void USceneManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void USceneManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool USceneManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void USceneManager::OnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::OnWorldMatchStarting(InWorld);

	CompassActor = Cast<ACompassActor>(UGameplayStatics::GetActorOfClass(this, ACompassActor::StaticClass()));
	MapScaleActor = Cast<AMapScaleActor>(UGameplayStatics::GetActorOfClass(this, AMapScaleActor::StaticClass()));
}

void USceneManager::OnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::OnWorldEndPlay(InWorld);
}

TArray<AActor*> USceneManager::FindActors(const FFindActorHandle& FindActorHandle, const bool bUpdate)
{
	auto FindActorInternal = [this](const FFindActorHandle& InFindActorHandle)
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
	};

	if (FFoundActorHandle* FoundActorHandle = FoundActorHandles.FindByKey(FindActorHandle))
	{
		if (bUpdate)
		{
			FoundActorHandle->FoundActors = FindActorInternal(FindActorHandle);
		}

		return FoundActorHandle->FoundActors;
	}
	else
	{
		FFoundActorHandle NewFoundActorHandle;
		NewFoundActorHandle.FindActorHandle = FindActorHandle;
		NewFoundActorHandle.FoundActors = FindActorInternal(FindActorHandle);

		FoundActorHandles.AddUnique(NewFoundActorHandle);
		return FoundActorHandle->FoundActors;
	}
}

float USceneManager::GetPlayerPointToNorthAngle(int32 PlayerIndex) const
{
	if (!IsValid(CompassActor))
	{
		DLOG(DLogWorld, Log, TEXT("CompassActor Is NULL"))
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

float USceneManager::GetWorldElevationOriginHeight() const
{
	if (!IsValid(CompassActor))
	{
		DLOG(DLogWorld, Log, TEXT("CompassActor Is NULL"))
		return 0.f;
	}

	return CompassActor->GetActorLocation().Z;
}
