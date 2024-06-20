// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode.h"

#include "ActiveNodeSubsystem.h"

AActiveNode::AActiveNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bAlwaysUpdate(true)
	, bComponentUpdate(true)
	, bInitialized(false)
	, bActive(false)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(USceneComponent::GetDefaultSceneRootVariableName());
	
#if WITH_EDITORONLY_DATA
	bIsSpatiallyLoaded = false;
#endif
	PrimaryActorTick.bCanEverTick = true;
}

void AActiveNode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(UActiveNodeSubsystem* ActiveNodeSubsystem = UActiveNodeSubsystem::Get(this))
	{
		ActiveNodeSubsystem->RegisterNode(NodeTag, this);
	}
}

void AActiveNode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(UActiveNodeSubsystem* ActiveNodeSubsystem = UActiveNodeSubsystem::Get(this))
	{
		ActiveNodeSubsystem->UnRegisterNode(NodeTag);
	}
}

bool AActiveNode::Login(const UObject* WorldContextObject, bool bReInit)
{
	if(bActive)
	{
		ReLogin(WorldContextObject, bReInit);
		return true;
	}
	
	return UActiveNodeSubsystem::Get(WorldContextObject)->ChangeNode(NodeTag, bReInit);
}

void AActiveNode::ReLogin(const UObject* WorldContextObject, bool bReInit)
{
	return UActiveNodeSubsystem::Get(WorldContextObject)->ReLoginNode(bReInit);
}