// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuEntity.h"

#include "BPFunctions/BPFunctions_GameplayTag.h"

UMenuEntity::UMenuEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsRoot = false;
	bIsGroup = false;
}

void UMenuEntity::Initialize()
{
	Super::Initialize();

	const FGameplayTag RootMenuTag = FGameplayTag::RequestGameplayTag("UI.Menu");
	if (UBPFunctions_GameplayTag::GetDirectGameplayTagParent(MenuTag) == RootMenuTag)
	{
		bIsRoot = true;
	}
}

void UMenuEntity::DeInitialize()
{
	Super::DeInitialize();
}
