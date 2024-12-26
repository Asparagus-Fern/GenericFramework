// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Manager.h"

#include "Manager/ManagerActor.h"
#include "Manager/ManagerProxy.h"

UManagerProxy* UBPFunctions_Manager::GetManagerProxy()
{
	return UManagerProxy::Get();
}

AManagerActor* UBPFunctions_Manager::GetManagerActorByClass(const TSubclassOf<AManagerActor> InClass)
{
	ensure(InClass);
	return GetManagerProxy()->GetManager<AManagerActor>();
}
