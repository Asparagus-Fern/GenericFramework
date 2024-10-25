// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor/FloorBodyComponent.h"

#include "Floor/FloorStaticMeshComponent.h"

UFloorBodyComponent::FOnFloorBodyRefresh UFloorBodyComponent::OnFloorBodyRefresh;

UFloorBodyComponent::UFloorBodyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFloorBodyComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFloorBodyComponent::OnRegister()
{
	Super::OnRegister();
	NativeOnRefresh();
}

void UFloorBodyComponent::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();

	for (const auto& Child : BodyComponents)
	{
		GetOwner()->RemoveInstanceComponent(Child);
		Child->DestroyComponent();
	}

	BodyComponents.Reset();

	for (auto& StaticMesh : BodyStaticMeshes)
	{
		if (!StaticMesh)
		{
			continue;
		}

		UFloorStaticMeshComponent* BodyStaticMeshComponent = Cast<UFloorStaticMeshComponent>(GetOwner()->AddComponentByClass(UFloorStaticMeshComponent::StaticClass(), true, FTransform::Identity, false));
		BodyComponents.Add(BodyStaticMeshComponent);

		BodyStaticMeshComponent->SetStaticMesh(StaticMesh);
		BodyStaticMeshComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

		GetOwner()->AddInstanceComponent(BodyStaticMeshComponent);
	}

	OnFloorBodyRefresh.Broadcast(this);
}
