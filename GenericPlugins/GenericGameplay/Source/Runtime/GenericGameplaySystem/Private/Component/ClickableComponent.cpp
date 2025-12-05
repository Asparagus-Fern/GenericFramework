// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/ClickableComponent.h"

#include "GameplayType.h"
#include "Engine/StaticMeshActor.h"
#include "Type/DebugType.h"

UClickableComponent::UClickableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UClickableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UClickableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (auto& BindingComponent : BindingComponents)
	{
		if (BindingComponent.IsValid())
		{
			if (bEnableCursorOverEvent)
			{
				BindingComponent->OnBeginCursorOver.RemoveAll(this);
				BindingComponent->OnEndCursorOver.RemoveAll(this);
			}

			if (bEnableClickedEvent)
			{
				BindingComponent->OnClicked.RemoveAll(this);
				BindingComponent->OnReleased.RemoveAll(this);
			}

			if (bEnableTouchEvent)
			{
				BindingComponent->OnInputTouchBegin.RemoveAll(this);
				BindingComponent->OnInputTouchEnd.RemoveAll(this);
			}

			if (bEnableTouchDragEvent)
			{
				BindingComponent->OnInputTouchEnter.RemoveAll(this);
				BindingComponent->OnInputTouchLeave.RemoveAll(this);
			}
		}
	}
}

void UClickableComponent::AddClickableStaticMesh(AStaticMeshActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogGameplay, Error, TEXT("Actor Is InValid"))
		return;
	}

	AddClickablePrimitiveComponent(InActor->GetStaticMeshComponent());
}

void UClickableComponent::AddClickablePrimitiveComponent(UPrimitiveComponent* InComponent)
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogGameplay, Error, TEXT("Component Is InValid"))
		return;
	}

	if (bEnableCursorOverEvent)
	{
		InComponent->OnBeginCursorOver.AddUniqueDynamic(this, &UClickableComponent::OnComponentBeginCursorOver);
		InComponent->OnEndCursorOver.AddUniqueDynamic(this, &UClickableComponent::OnComponentEndCursorOver);
	}

	if (bEnableClickedEvent)
	{
		InComponent->OnClicked.AddUniqueDynamic(this, &UClickableComponent::OnComponentClicked);
		InComponent->OnReleased.AddUniqueDynamic(this, &UClickableComponent::OnComponentReleased);
	}

	if (bEnableTouchEvent)
	{
		InComponent->OnInputTouchBegin.AddUniqueDynamic(this, &UClickableComponent::OnComponentInputTouchBegin);
		InComponent->OnInputTouchEnd.AddUniqueDynamic(this, &UClickableComponent::OnComponentInputTouchEnd);
	}

	if (bEnableTouchDragEvent)
	{
		InComponent->OnInputTouchEnter.AddUniqueDynamic(this, &UClickableComponent::OnComponentInputTouchEnter);
		InComponent->OnInputTouchLeave.AddUniqueDynamic(this, &UClickableComponent::OnComponentInputTouchLeave);
	}

	BindingComponents.Add(InComponent);
}

void UClickableComponent::OnComponentBeginCursorOver(UPrimitiveComponent* TouchedComponent)
{
}

void UClickableComponent::OnComponentEndCursorOver(UPrimitiveComponent* TouchedComponent)
{
}

void UClickableComponent::OnComponentClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
}

void UClickableComponent::OnComponentReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
}

void UClickableComponent::OnComponentInputTouchBegin(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
}

void UClickableComponent::OnComponentInputTouchEnd(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
}

void UClickableComponent::OnComponentInputTouchEnter(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
}

void UClickableComponent::OnComponentInputTouchLeave(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
}
