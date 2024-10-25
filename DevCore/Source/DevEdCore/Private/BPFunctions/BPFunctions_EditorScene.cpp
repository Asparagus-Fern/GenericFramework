// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_EditorScene.h"

#include "Selection.h"

TArray<AActor*> UBPFunctions_EditorScene::GetSelectedActor()
{
	TArray<AActor*> SelectedActors;
	GEditor->GetSelectedActors()->GetSelectedObjects(SelectedActors);
	return SelectedActors;
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
	const TArray<AActor*> Actors = GetSelectedActor();
	SelectNone();
	SelectActors(Actors, true);
}
