// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Building/BuildingActor.h"

#include "Floor/FloorActor.h"
#include "Floor/FloorBodyComponent.h"

ABuildingActor::FBuildingEvent ABuildingActor::OnBuildingActiveStateChanged;

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

	OnBuildingActiveStateChanged.AddUObject(this, &ABuildingActor::HandleBuildingActiveStateChanged);
}

void ABuildingActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnBuildingActiveStateChanged.RemoveAll(this);
}

void ABuildingActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	NativeOnRefresh();
}

void ABuildingActor::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();

	UFloorBodyComponent::OnBodyClicked.AddUObject(this, &ABuildingActor::HandleBodyClicked);

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

	UFloorBodyComponent::OnBodyClicked.RemoveAll(this);
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
				NewFloorActor->SetOwnerBuilding(this);

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

void ABuildingActor::HandleBuildingActiveStateChanged(ABuildingActor* InBuildingActor)
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

void ABuildingActor::HandleBodyClicked(UFloorBodyComponent* BodyComponent)
{
	for (const auto& ChildActorComponent : FloorComponents)
	{
		if (const AFloorActor* FloorActor = Cast<AFloorActor>(ChildActorComponent->GetChildActor()))
		{
			if (FloorActor->FloorBodyComponent == BodyComponent)
			{
				SelectFloorInternal(ChildActorComponent);
			}
		}
	}
}

void ABuildingActor::SelectFloor(int32 InFloor)
{
	if (FloorComponents.IsValidIndex(InFloor - 1))
	{
		SelectFloorInternal(FloorComponents[InFloor - 1]);
	}
}

void ABuildingActor::DeselectFloor()
{
	SelectFloorInternal(nullptr);
}

UChildActorComponent* ABuildingActor::GetFloorComponent(int32 InFloor)
{
	if (FloorComponents.IsValidIndex(InFloor - 1))
	{
		return FloorComponents[InFloor - 1];
	}
	return nullptr;
}

AFloorActor* ABuildingActor::GetFloorActor(int32 InFloor)
{
	if (const UChildActorComponent* FloorComponent = GetFloorComponent(InFloor))
	{
		return Cast<AFloorActor>(FloorComponent->GetChildActor());
	}
	return nullptr;
}

UChildActorComponent* ABuildingActor::GetSelectedFloorComponent() const
{
	return SelectedFloorComponent;
}

AFloorActor* ABuildingActor::GetSelectedFloorActor()
{
	if (const UChildActorComponent* FloorComponent = GetSelectedFloorComponent())
	{
		return Cast<AFloorActor>(FloorComponent->GetChildActor());
	}
	return nullptr;
}

int32 ABuildingActor::GetSelectedFloor()
{
	if (AFloorActor* FloorActor = GetSelectedFloorActor())
	{
		return FloorActor->GetFloor();
	}
	return 0;
}

void ABuildingActor::SelectFloorInternal(UChildActorComponent* InFloorComponent)
{
	/* InFloorComponent为空表示清空当前所选楼层 */
	if (!IsValid(InFloorComponent))
	{
		if (IsValid(SelectedFloorComponent))
		{
			SetFloorActorSelection(SelectedFloorComponent, false);
			SelectedFloorComponent = nullptr;
		}

		return;
	}

	if (SelectedFloorComponent != InFloorComponent)
	{
		if (IsValid(SelectedFloorComponent))
		{
			SetFloorActorSelection(SelectedFloorComponent, false);
		}

		SelectedFloorComponent = InFloorComponent;
		SetFloorActorSelection(SelectedFloorComponent, true);
	}
}

void ABuildingActor::SetFloorActorSelection(const UChildActorComponent* FloorComponent, const bool bIsSelected)
{
	if (IsValid(FloorComponent))
	{
		if (AFloorActor* FloorActor = Cast<AFloorActor>(FloorComponent->GetChildActor()))
		{
			FloorActor->NativeHandleFloorSelectionChanged(bIsSelected);
		}
	}
}
