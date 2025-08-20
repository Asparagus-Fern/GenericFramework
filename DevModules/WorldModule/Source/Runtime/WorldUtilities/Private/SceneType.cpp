#include "SceneType.h"

#include "BPFunctions/BPFunctions_Math.h"

DEFINE_LOG_CATEGORY(GenericLogWorld);

/* ==================== FFindActorHandle ==================== */

FFindActorHandle::FFindActorHandle()
	: ID(FGuid::NewGuid())
{
}

FFindActorHandle::FFindActorHandle(FName InActorTag)
	: FindActorMethod(EFindActorMethod::Tag),
	  ActorTag(InActorTag)
{
}

FFindActorHandle::FFindActorHandle(TSubclassOf<AActor> InActorClass)
	: FindActorMethod(EFindActorMethod::Class),
	  ActorClass(InActorClass)
{
}

FFindActorHandle::FFindActorHandle(TSubclassOf<UInterface> InActorInterface)
	: FindActorMethod(EFindActorMethod::Interface),
	  ActorInterface(InActorInterface)
{
}

FFindActorHandle::FFindActorHandle(TSubclassOf<AActor> InActorClass, FName InActorTag)
	: FindActorMethod(EFindActorMethod::ClassAndTag),
	  ActorTag(InActorTag),
	  ActorClass(InActorClass)
{
}

bool FFindActorHandle::GetIsValid() const
{
	return (FindActorMethod == EFindActorMethod::Class && IsValid(ActorClass))
		|| (FindActorMethod == EFindActorMethod::Tag && !ActorTag.IsNone())
		|| (FindActorMethod == EFindActorMethod::ClassAndTag && IsValid(ActorClass) && !ActorTag.IsNone())
		|| (FindActorMethod == EFindActorMethod::Interface && IsValid(ActorInterface));
}

/* ==================== UHandleActorLocation ==================== */

void UHandleActor::ExecuteHandle(TArray<AActor*> InActors)
{
	ExecuteHandle(InActors, 1.f);
}

bool UHandleActorLocation::CanExecuteHandle()
{
	return bHandleActorLocation || bHandleActorLocationOffset;
}

void UHandleActorLocation::PreExecuteHandle(TArray<AActor*> InActors)
{
	Super::PreExecuteHandle(InActors);

	for (const auto& InActor : InActors)
	{
		OriginActorLocation.Add(InActor->GetActorLocation());
	}
}

void UHandleActorLocation::ExecuteHandle(TArray<AActor*> InActors, float Alpha)
{
	for (auto ActorIt = 0; ActorIt < InActors.Num(); ActorIt++)
	{
		if (bHandleActorLocation)
		{
			InActors[ActorIt]->SetActorLocation(FMath::Lerp(OriginActorLocation[ActorIt], NewActorLocation, Alpha));
		}

		if (bHandleActorLocationOffset)
		{
			InActors[ActorIt]->SetActorLocation(OriginActorLocation[ActorIt] + FMath::Lerp(FVector::ZeroVector, NewActorLocationOffset, Alpha));
		}
	}
}

void UHandleActorLocation::PostExecuteHandle(TArray<AActor*> InActors)
{
	Super::PostExecuteHandle(InActors);
	OriginActorLocation.Reset();
}

/* ==================== UHandleActorRotation ==================== */

bool UHandleActorRotation::CanExecuteHandle()
{
	return bHandleActorRotation || bHandleActorRotationOffset;
}

void UHandleActorRotation::PreExecuteHandle(TArray<AActor*> InActors)
{
	Super::PreExecuteHandle(InActors);

	for (const auto& InActor : InActors)
	{
		OriginActorRotation.Add(InActor->GetActorRotation());
	}
}

void UHandleActorRotation::ExecuteHandle(TArray<AActor*> InActors, float Alpha)
{
	for (auto ActorIt = 0; ActorIt < InActors.Num(); ActorIt++)
	{
		if (bHandleActorRotation)
		{
			InActors[ActorIt]->SetActorRotation(FMath::Lerp(OriginActorRotation[ActorIt], NewActorRotation, Alpha));
		}

		if (bHandleActorRotationOffset)
		{
			InActors[ActorIt]->SetActorRotation(OriginActorRotation[ActorIt] + FMath::Lerp(FRotator::ZeroRotator, NewActorRotationOffset, Alpha));
		}
	}
}

void UHandleActorRotation::PostExecuteHandle(TArray<AActor*> InActors)
{
	Super::PostExecuteHandle(InActors);
	OriginActorRotation.Reset();
}

/* ==================== UHandleActorScale ==================== */

bool UHandleActorScale::CanExecuteHandle()
{
	return bHandleActorScale || bHandleActorScaleOffset;
}

void UHandleActorScale::PreExecuteHandle(TArray<AActor*> InActors)
{
	Super::PreExecuteHandle(InActors);

	for (const auto& InActor : InActors)
	{
		OriginActorLocation.Add(InActor->GetActorScale());
	}
}

void UHandleActorScale::ExecuteHandle(TArray<AActor*> InActors, float Alpha)
{
	for (auto ActorIt = 0; ActorIt < InActors.Num(); ActorIt++)
	{
		if (bHandleActorScale)
		{
			InActors[ActorIt]->SetActorScale3D(FMath::Lerp(OriginActorLocation[ActorIt], NewActorScale, Alpha));
		}

		if (bHandleActorScaleOffset)
		{
			InActors[ActorIt]->SetActorScale3D(OriginActorLocation[ActorIt] + FMath::Lerp(FVector::ZeroVector, NewActorScaleOffset, Alpha));
		}
	}
}

void UHandleActorScale::PostExecuteHandle(TArray<AActor*> InActors)
{
	Super::PostExecuteHandle(InActors);
	OriginActorLocation.Reset();
}

/* ==================== UHandleActorHiddenInGame ==================== */

bool UHandleActorHiddenInGame::CanExecuteHandle()
{
	return bHandleActorHiddenInGame;
}

void UHandleActorHiddenInGame::ExecuteHandle(TArray<AActor*> InActors)
{
	for (const auto& InActor : InActors)
	{
		if (bHandleActorHiddenInGame)
		{
			InActor->SetActorHiddenInGame(NewActorHiddenInGame);
		}
	}
}
