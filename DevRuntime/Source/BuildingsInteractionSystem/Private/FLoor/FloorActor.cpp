// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor/FloorActor.h"

#include "Floor/FloorBodyComponent.h"
#include "Floor/FloorMarkPointComponent.h"

AFloorActor::AFloorActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<UFloorBodyComponent>("Root");
	RootComponent = SceneComponent;

	FloorComponent = CreateDefaultSubobject<UFloorBodyComponent>("Body");
	FloorComponent->SetupAttachment(RootComponent);

	FloorMarkPointComponent = CreateDefaultSubobject<UFloorMarkPointComponent>("MarkPoint");
	FloorMarkPointComponent->SetupAttachment(RootComponent);
}

void AFloorActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFloorActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// auto GetGoundingBoxMin = [](FVector& Min, const FBox& InBoundingBox)
	// {
	// 	Min.X = (InBoundingBox.Min.X < Min.X) ? InBoundingBox.Min.X : Min.X;
	// 	Min.Y = (InBoundingBox.Min.Y < Min.Y) ? InBoundingBox.Min.Y : Min.Y;
	// 	Min.Z = (InBoundingBox.Min.Z < Min.Z) ? InBoundingBox.Min.Z : Min.Z;
	// };
	//
	// auto GetGoundingBoxMax = [](FVector& Max, const FBox& InBoundingBox)
	// {
	// 	Max.X = (InBoundingBox.Max.X > Max.X) ? InBoundingBox.Max.X : Max.X;
	// 	Max.Y = (InBoundingBox.Max.Y > Max.Y) ? InBoundingBox.Max.Y : Max.Y;
	// 	Max.Z = (InBoundingBox.Max.Z > Max.Z) ? InBoundingBox.Max.Z : Max.Z;
	// };
	//
	// float LocationZ = 0.f;

	// for (auto It = FloorBodyInfos.CreateConstIterator(); It; ++It)
	// {
	// FVector BoundingBoxMin = FVector(UE_BIG_NUMBER,UE_BIG_NUMBER,UE_BIG_NUMBER);
	// FVector BoundingBoxMax = FVector(UE_SMALL_NUMBER,UE_SMALL_NUMBER,UE_SMALL_NUMBER);

	// USceneComponent* TransientSceneComponent = Cast<USceneComponent>(AddComponentByClass(USceneComponent::StaticClass(), true, FTransform::Identity, false));
	// TransientSceneComponent->AttachToComponent(SceneBodyComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	// if (!It->StaticMesh)
	// {
	// 	continue;
	// }
	//
	// UFloorStaticMeshComponent* BodyStaticMeshComponent = Cast<UFloorStaticMeshComponent>(AddComponentByClass(UFloorStaticMeshComponent::StaticClass(), true, FTransform::Identity, false));
	// BodyStaticMeshComponent->AttachToComponent(SceneBodyComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	//
	// BodyStaticMeshComponent->SetStaticMesh(It->StaticMesh);
	// BodyStaticMeshComponent->SetRelativeTransform(It->Transform);

	// BodyStaticMeshComponent->SetFloor(It.GetIndex());

	// const FBox BoundingBox = TransientFloorStaticMeshComponent->Bounds.GetBox();
	// GetGoundingBoxMin(BoundingBoxMin, BoundingBox);
	// GetGoundingBoxMax(BoundingBoxMax, BoundingBox);


	// if (It.GetIndex())
	// {
	// 	TransientSceneComponent->SetRelativeLocation(FVector(0.f, 0.f, LocationZ));
	// }
	//
	// LocationZ += (BoundingBoxMax - BoundingBoxMin).Z;
	// }
}
