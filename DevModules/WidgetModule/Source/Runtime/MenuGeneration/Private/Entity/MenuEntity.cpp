// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuEntity.h"

UMenuEntity::UMenuEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMenuEntity::Initialize()
{
	Super::Initialize();
}

void UMenuEntity::DeInitialize()
{
	Super::DeInitialize();
}

void UMenuEntity::OnActived_Implementation()
{
	Super::OnActived_Implementation();
}

void UMenuEntity::OnInactived_Implementation()
{
	Super::OnInactived_Implementation();
}

void UMenuEntity::OnSelected_Implementation()
{
	Super::OnSelected_Implementation();
	NativeOnActived();
}

void UMenuEntity::OnDeSelected_Implementation()
{
	Super::OnDeSelected_Implementation();
	NativeOnInactived();
}
