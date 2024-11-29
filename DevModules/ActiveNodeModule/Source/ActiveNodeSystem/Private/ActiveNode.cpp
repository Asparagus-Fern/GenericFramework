// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode.h"

#include "ActiveNodeSubsystem.h"

AActiveNode::AActiveNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bAlwaysUpdate(true)
	, bComponentUpdate(false)
	, bInitialized(false)
	, bActive(false)
{
	
#if WITH_EDITORONLY_DATA
	bIsSpatiallyLoaded = false;
#endif

	SetHidden(false);
	PrimaryActorTick.bCanEverTick = true;
}

bool AActiveNode::IsActivationNode() const
{
	const UWorld* World = GetWorld();
	if(World != nullptr)
	{
		if(const UActiveNodeSubsystem* ActiveNodeSubsystem =  UActiveNodeSubsystem::Get(World))
		{
			return ActiveNodeSubsystem->GetCurrentActiveNode() == this && bInitialized && bActive ;
		}
	}
	return false;
}