// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreManager.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

#if WITH_EDITOR

void UCoreManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	TryUpdateDefaultConfigFile();
}

#endif

UWorld* UCoreManager::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("Manager: %s has a null OuterPrivate in UCoreManager::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}

void UCoreManager::NativeOnCreate()
{
	GConfig->Flush(false, *GetSaveIniPath());
	LoadConfig(GetClass(), *GetSaveIniPath());

	IProcedureBaseInterface::NativeOnCreate();
	IProcedureBaseInterface::Execute_OnCreate(this);

	TryUpdateDefaultConfigFile();
	DEBUG(Debug_Manager, Log, TEXT("On Created : %s"), *GetName());
}

void UCoreManager::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	IProcedureBaseInterface::Execute_OnRefresh(this);
}

void UCoreManager::NativeOnDestroy()
{
	TryUpdateDefaultConfigFile();

	IProcedureBaseInterface::NativeOnDestroy();
	IProcedureBaseInterface::Execute_OnDestroy(this);

	DEBUG(Debug_Manager, Log, TEXT("On Destroy : %s"), *GetName());
}

void UCoreManager::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);

	DEBUG(Debug_Manager, Log, TEXT("On Actived : %s"), *GetName());
}

void UCoreManager::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);

	DEBUG(Debug_Manager, Log, TEXT("On Inactived : %s"), *GetName());
}

void UCoreManager::NativeOnBeginPlay()
{
	Execute_OnBeginPlay(this);
}

void UCoreManager::NativeOnEndPlay()
{
	Execute_OnEndPlay(this);
}

#undef LOCTEXT_NAMESPACE
