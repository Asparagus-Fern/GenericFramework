// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_EditorScene.h"

#include "Selection.h"

TArray<AActor*> UBPFunctions_EditorScene::GetSelectedActors()
{
	TArray<AActor*> SelectedActors;
	GEditor->GetSelectedActors()->GetSelectedObjects(SelectedActors);
	return SelectedActors;
}

TArray<UActorComponent*> UBPFunctions_EditorScene::GetSelectedComponents()
{
	TArray<UActorComponent*> SelectedComponents;
	GEditor->GetSelectedComponents()->GetSelectedObjects(SelectedComponents);
	return SelectedComponents;
}

void UBPFunctions_EditorScene::SelectNone()
{
	GEditor->SelectNone(false, true);
}

void UBPFunctions_EditorScene::SelectActor(AActor* InActor, bool bInSelected)
{
	GEditor->SelectActor(InActor, bInSelected, true);
}

void UBPFunctions_EditorScene::SelectActors(TArray<AActor*> InActors, bool bInSelected)
{
	for (const auto& Actor : InActors)
	{
		GEditor->SelectActor(Actor, bInSelected, true);
	}
}

void UBPFunctions_EditorScene::SelectComponent(UActorComponent* InComponent, bool bInSelected)
{
	GEditor->SelectComponent(InComponent, bInSelected, true);
}

void UBPFunctions_EditorScene::SelectComponents(TArray<UActorComponent*> InComponents, bool bInSelected)
{
	for (const auto& Component : InComponents)
	{
		GEditor->SelectComponent(Component, bInSelected, true);
	}
}

void UBPFunctions_EditorScene::RefreshSelection()
{
	const TArray<AActor*> Actors = GetSelectedActors();
	const TArray<UActorComponent*> Components = GetSelectedComponents();

	SelectNone();

	if (!Actors.IsEmpty())
	{
		SelectActors(Actors, true);
	}

	if (!Components.IsEmpty())
	{
		SelectComponents(Components, true);
	}
}
