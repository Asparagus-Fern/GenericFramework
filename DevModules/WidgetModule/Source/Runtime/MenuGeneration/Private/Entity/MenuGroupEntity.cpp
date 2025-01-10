// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuGroupEntity.h"

UMenuGroupEntity::UMenuGroupEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsGroup = true;
}

void UMenuGroupEntity::Initialize()
{
	Super::Initialize();
}

void UMenuGroupEntity::DeInitialize()
{
	Super::DeInitialize();
}
