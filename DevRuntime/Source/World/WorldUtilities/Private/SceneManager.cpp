// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneManager.h"

#include "Kismet/GameplayStatics.h"
#include "SceneManagerSetting.h"
#include "Compass/CompassActor.h"

USceneManager::USceneManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickable = true;
}

bool USceneManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && USceneManagerSetting::Get()->bEnableSubsystem;
}

void USceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DLOG(DLogWorld, Log, TEXT("%f"), GetPlayerPointToNorthAngle(0))
}

void USceneManager::NativeOnActived()
{
	Super::NativeOnActived();
	CompassActor = Cast<ACompassActor>(UGameplayStatics::GetActorOfClass(this, ACompassActor::StaticClass()));
}

void USceneManager::NativeOnInactived()
{
	Super::NativeOnInactived();
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
	const FVector LookForward = UGameplayStatics::GetPlayerCameraManager(this, PlayerIndex)->GetActorForwardVector().GetSafeNormal2D();

	float DegreesNorth = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(WorldNorthDirection, LookForward)));
	const float DegreesEast = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(WorldEastDirection, LookForward)));

	if (DegreesEast > 90.f)
	{
		DegreesNorth = -DegreesNorth;
	}

	return DegreesNorth;
}
