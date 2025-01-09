// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuEntity.h"

UMenuEntity::UMenuEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsRoot = false;
	bIsGroup = false;
}

void UMenuEntity::Initialize()
{
	Super::Initialize();
}

void UMenuEntity::DeInitialize()
{
	Super::DeInitialize();
}
