// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerActor.h"

#include "Manager/ManagerProxy.h"

AManagerActor::AManagerActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AManagerActor::BeginPlay()
{
	Super::BeginPlay();
	RegisterManager(this);
}

void AManagerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnRegisterManager();
}

int32 AManagerActor::GetManagerOrder()
{
	return ManagerOrder;
}

void AManagerActor::SetManagerOrder(int32 InManagerOrder)
{
	ManagerOrder = InManagerOrder;
	UManagerProxy::Get()->SortManagers();
}
