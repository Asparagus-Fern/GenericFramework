// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor/FloorBodyComponent.h"

#include "Interface/FloorBodyInteractionInterface.h"

UFloorBodyComponent::FFloorBodyEvent UFloorBodyComponent::OnBeginCursorOverBody;
UFloorBodyComponent::FFloorBodyEvent UFloorBodyComponent::OnEndCursorOverBody;
UFloorBodyComponent::FFloorBodyEvent UFloorBodyComponent::OnBodyClicked;

UFloorBodyComponent::UFloorBodyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFloorBodyComponent::OnRegister()
{
	Super::OnRegister();

	Refresh();
}

#if WITH_EDITOR

void UFloorBodyComponent::RefreshFloor()
{
	Refresh();
}

#endif

void UFloorBodyComponent::Refresh()
{
	BodyComponents.Reset();

	TArray<UStaticMeshComponent*> ChildrenToRemove;
	TArray<TObjectPtr<UStaticMesh>> ChildrenToAdd;

	/* 遍历当前所有子组件，确定需要增加或移除的组件 */
	for (const auto& Child : GetOwner()->GetInstanceComponents())
	{
		if (UStaticMeshComponent* BodyComponent = Cast<UStaticMeshComponent>(Child))
		{
			if (!BodyComponents.Contains(BodyComponent) && BodyStaticMeshes.Contains(BodyComponent->GetStaticMesh()))
			{
				BodyComponents.Add(BodyComponent);
			}

			if (!BodyStaticMeshes.Contains(BodyComponent->GetStaticMesh()))
			{
				ChildrenToRemove.Add(BodyComponent);
			}

			ChildrenToAdd.Add(BodyComponent->GetStaticMesh());
		}
	}

	const TSet<TObjectPtr<UStaticMesh>> Previous(ChildrenToAdd);
	const TSet<TObjectPtr<UStaticMesh>> Current(BodyStaticMeshes);
	ChildrenToAdd = Current.Difference(Previous).Array();

	/* 添加组件 */
	for (auto& ItemToAdd : ChildrenToAdd)
	{
		/* 跳过无效StaticMesh */
		if (!ItemToAdd)
		{
			continue;
		}

		UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this);
		BodyComponents.Add(StaticMeshComponent);

		StaticMeshComponent->SetStaticMesh(ItemToAdd);
		StaticMeshComponent->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		StaticMeshComponent->RegisterComponent();
		GetOwner()->AddInstanceComponent(StaticMeshComponent);
	}

	/* 移除组件 */
	for (const auto& ItemToRemove : ChildrenToRemove)
	{
		GetOwner()->RemoveInstanceComponent(ItemToRemove);
		ItemToRemove->DestroyComponent();
	}
}

void UFloorBodyComponent::GetBodyBoundingBox(FVector& BoundingBoxMin, FVector& BoundingBoxMax)
{
	auto GetGoundingBoxMin = [](FVector& Min, const FBox& InBoundingBox)
	{
		Min.X = (InBoundingBox.Min.X < Min.X) ? InBoundingBox.Min.X : Min.X;
		Min.Y = (InBoundingBox.Min.Y < Min.Y) ? InBoundingBox.Min.Y : Min.Y;
		Min.Z = (InBoundingBox.Min.Z < Min.Z) ? InBoundingBox.Min.Z : Min.Z;
	};

	auto GetGoundingBoxMax = [](FVector& Max, const FBox& InBoundingBox)
	{
		Max.X = (InBoundingBox.Max.X > Max.X) ? InBoundingBox.Max.X : Max.X;
		Max.Y = (InBoundingBox.Max.Y > Max.Y) ? InBoundingBox.Max.Y : Max.Y;
		Max.Z = (InBoundingBox.Max.Z > Max.Z) ? InBoundingBox.Max.Z : Max.Z;
	};

	BoundingBoxMin = FVector(UE_BIG_NUMBER,UE_BIG_NUMBER,UE_BIG_NUMBER);
	BoundingBoxMax = FVector(UE_SMALL_NUMBER,UE_SMALL_NUMBER,UE_SMALL_NUMBER);

	for (auto It = BodyComponents.CreateConstIterator(); It; ++It)
	{
		if (const UStaticMeshComponent* BodyComponent = *It)
		{
			const FBox BoundingBox = BodyComponent->Bounds.GetBox();
			GetGoundingBoxMin(BoundingBoxMin, BoundingBox);
			GetGoundingBoxMax(BoundingBoxMax, BoundingBox);
		}
	}
}

void UFloorBodyComponent::AddBodyMouseDelegate()
{
	for (const auto& BodyComponent : BodyComponents)
	{
		BodyComponent->OnBeginCursorOver.AddDynamic(this, &UFloorBodyComponent::HandleBeginCursorOverInternal);
		BodyComponent->OnEndCursorOver.AddDynamic(this, &UFloorBodyComponent::HandleEndCursorOverInternal);
		BodyComponent->OnClicked.AddDynamic(this, &UFloorBodyComponent::HandleOnClickedInternal);
	}
}

void UFloorBodyComponent::RemoveBodyMouseDelegate()
{
	for (const auto& BodyComponent : BodyComponents)
	{
		BodyComponent->OnBeginCursorOver.RemoveAll(this);
		BodyComponent->OnEndCursorOver.RemoveAll(this);
		BodyComponent->OnClicked.RemoveAll(this);
	}
}

void UFloorBodyComponent::HandleBeginCursorOverInternal(UPrimitiveComponent* TouchedComponent)
{
	OnBeginCursorOverBody.Broadcast(this);
	IFloorBodyInteractionInterface::Execute_HandleBeginCursorOverBody(GetOwner(), this);
}

void UFloorBodyComponent::HandleEndCursorOverInternal(UPrimitiveComponent* TouchedComponent)
{
	OnEndCursorOverBody.Broadcast(this);
	IFloorBodyInteractionInterface::Execute_HandleEndCursorOverBody(GetOwner(), this);
}

void UFloorBodyComponent::HandleOnClickedInternal(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	OnBodyClicked.Broadcast(this);
	IFloorBodyInteractionInterface::Execute_HandleBodyClicked(GetOwner(), this);
}
