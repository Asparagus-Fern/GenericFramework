// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor/FloorBodyComponent.h"

UFloorBodyComponent::FOnFloorBodyRefresh UFloorBodyComponent::OnFloorBodyRefresh;

UFloorBodyComponent::UFloorBodyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFloorBodyComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& BodyComponent : BodyComponents)
	{
		BodyComponent->OnBeginCursorOver.AddDynamic(this, &UFloorBodyComponent::HandleBeginCursorOver);
		BodyComponent->OnEndCursorOver.AddDynamic(this, &UFloorBodyComponent::HandleEndCursorOver);
		BodyComponent->OnClicked.AddDynamic(this, &UFloorBodyComponent::HandleOnClicked);
	}
}

void UFloorBodyComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (const auto& BodyComponent : BodyComponents)
	{
		BodyComponent->OnBeginCursorOver.RemoveAll(this);
		BodyComponent->OnEndCursorOver.RemoveAll(this);
		BodyComponent->OnClicked.RemoveAll(this);
	}
}

void UFloorBodyComponent::OnRegister()
{
	Super::OnRegister();

	BodyComponents.Reset();

	/* 查找指定的SceneComponent */
	SceneComponent = Cast<USceneComponent>(GetOwner()->FindComponentByTag(USceneComponent::StaticClass(), "BodyScene"));

	/* 不存在则创建 */
	if (!IsValid(SceneComponent))
	{
		SceneComponent = Cast<USceneComponent>(GetOwner()->AddComponentByClass(USceneComponent::StaticClass(), true, FTransform::Identity, false));
		SceneComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SceneComponent->ComponentTags.Add("BodyScene");
		GetOwner()->AddInstanceComponent(SceneComponent);
	}

	/* 查找已经挂在的StaticMeshComponent */
	TArray<UActorComponent*> FoundComponets = GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Body");
	for (const auto& FoundComponet : FoundComponets)
	{
		if (UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(FoundComponet))
		{
			BodyComponents.Add(Component);
		}
	}

	/* 如果BodyStaticMeshes为空，清除所有StaticMeshComponent */
	if (BodyStaticMeshes.IsEmpty())
	{
		for (const auto& Child : BodyComponents)
		{
			GetOwner()->RemoveInstanceComponent(Child);
			Child->DestroyComponent();
		}

		OnFloorBodyRefresh.Broadcast(this);
		return;
	}

	/* 从StaticMesh创建StaticMeshComponent */
	TArray<UStaticMeshComponent*> TempBodyComponents = BodyComponents;
	for (auto& StaticMesh : BodyStaticMeshes)
	{
		/* 跳过无效StaticMesh */
		if (!StaticMesh)
		{
			continue;
		}

		/* 跳过已有的StaticMeshComponent */
		if (UStaticMeshComponent* Component = GetComponentByStaticMesh(StaticMesh))
		{
			TempBodyComponents.Remove(Component);
			continue;
		}

		UStaticMeshComponent* BodyStaticMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->AddComponentByClass(UStaticMeshComponent::StaticClass(), true, FTransform::Identity, false));
		BodyComponents.Add(BodyStaticMeshComponent);

		BodyStaticMeshComponent->SetStaticMesh(StaticMesh);
		BodyStaticMeshComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		BodyStaticMeshComponent->ComponentTags.Add("Body");
		GetOwner()->AddInstanceComponent(BodyStaticMeshComponent);
	}

	/* 不在BodyStaticMeshes里的全部销毁 */
	for (const auto& TempBodyComponent : TempBodyComponents)
	{
		GetOwner()->RemoveInstanceComponent(TempBodyComponent);
		TempBodyComponent->DestroyComponent();
	}

	OnFloorBodyRefresh.Broadcast(this);
}

UStaticMeshComponent* UFloorBodyComponent::GetComponentByStaticMesh(TObjectPtr<UStaticMesh> StaticMesh)
{
	for (const auto& BodyComponent : BodyComponents)
	{
		if (BodyComponent->GetStaticMesh() == StaticMesh)
		{
			return BodyComponent;
		}
	}

	return nullptr;
}

void UFloorBodyComponent::HandleBeginCursorOver(UPrimitiveComponent* TouchedComponent)
{
}

void UFloorBodyComponent::HandleEndCursorOver(UPrimitiveComponent* TouchedComponent)
{
}

void UFloorBodyComponent::HandleOnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
}
