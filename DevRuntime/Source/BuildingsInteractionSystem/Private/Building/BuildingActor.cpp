// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/BuildingActor.h"

#include "Floor/FloorActor.h"
#include "Floor/FloorBodyComponent.h"

ABuildingActor::FBuildingEvent ABuildingActor::OnBuildingActived;

ABuildingActor::ABuildingActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();

	GetComponents(UChildActorComponent::StaticClass(), FloorComponents);
	FloorComponents.Sort([](const UChildActorComponent& ChildA, const UChildActorComponent& ChildB)
		{
			return Cast<AFloorActor>(ChildA.GetChildActor())->GetFloor() < Cast<AFloorActor>(ChildB.GetChildActor())->GetFloor();
		}
	);

	OnBuildingActived.AddUObject(this, &ABuildingActor::HandleBuildingActived);
}

void ABuildingActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnBuildingActived.RemoveAll(this);
}

void ABuildingActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	NativeOnRefresh();
}

void ABuildingActor::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();

	for (const auto& ChildActorComponent : FloorComponents)
	{
		Cast<AFloorActor>(ChildActorComponent->GetChildActor())->NativeOnActived();
	}
}

void ABuildingActor::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();

	for (const auto& ChildActorComponent : FloorComponents)
	{
		Cast<AFloorActor>(ChildActorComponent->GetChildActor())->NativeOnInactived();
	}
}

void ABuildingActor::OnRefresh_Implementation()
{
	IProcedureInterface::OnRefresh_Implementation();

	/* 移除所有楼层 */
	{
		TArray<UChildActorComponent*> ChildComponents;
		GetComponents(UChildActorComponent::StaticClass(), ChildComponents);

		for (const auto& ChildActorComponent : ChildComponents)
		{
			ChildActorComponent->DestroyComponent();
		}
	}

	/* 重新构建楼层 */
	{
		FVector SpawnLocation = FVector::ZeroVector;

		for (auto It = FloorClasses.CreateConstIterator(); It; ++It)
		{
			if (TSubclassOf<AFloorActor> FloorActorClass = *It)
			{
				UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(AddComponentByClass(UChildActorComponent::StaticClass(), false, FTransform(SpawnLocation), false));
				ChildActorComponent->SetChildActorClass(FloorActorClass);

				AFloorActor* NewFloorActor = Cast<AFloorActor>(ChildActorComponent->GetChildActor());
				NewFloorActor->SetFloor(It.GetIndex() + 1);

				FVector BoundingBoxMin = FVector::ZeroVector;
				FVector BoundingBoxMax = FVector::ZeroVector;
				NewFloorActor->FloorBodyComponent->GetBodyBoundingBox(BoundingBoxMin, BoundingBoxMax);

				SpawnLocation.Z += (BoundingBoxMax - BoundingBoxMin).Z;
			}
			else
			{
				SpawnLocation.Z += 300.f;
			}
		}
	}
}

void ABuildingActor::OnActived_Implementation()
{
	IProcedureInterface::OnActived_Implementation();
}

void ABuildingActor::OnInactived_Implementation()
{
	IProcedureInterface::OnInactived_Implementation();
}

#if WITH_EDITOR

void ABuildingActor::RefreshBuilding()
{
	NativeOnRefresh();
}

#endif

void ABuildingActor::HandleBuildingActived(ABuildingActor* InBuildingActor)
{
	if (InBuildingActor == this && !GetIsActived())
	{
		NativeOnActived();
	}
	else if (InBuildingActor != this && GetIsActived())
	{
		NativeOnInactived();
	}
}
