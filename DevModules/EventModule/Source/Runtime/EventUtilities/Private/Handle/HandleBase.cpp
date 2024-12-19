// Fill out your copyright notice in the Description page of Project Settings.

#include "Handle/HandleBase.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

FName UHandleBase::GetHandleName()
{
	return HandleName;
}

void UHandleBase::SetHandleName(FName InHandleName)
{
	HandleName = InHandleName;
}

FText UHandleBase::GetHandleDisplayName()
{
	return HandleDisplayName;
}

void UHandleBase::SetHandleDisplayName(FText InHandleDisplayName)
{
	HandleDisplayName = InHandleDisplayName;
}

bool UHandleBase::EqualID_Implementation(const UHandleBase* Other)
{
	return GetHandleID() == Other->GetHandleID();
}

bool UHandleBase::EqualName_Implementation(FName Other)
{
	return GetHandleName() == Other;
}

bool UHandleBase::NotEqualID_Implementation(const UHandleBase* Other)
{
	return !EqualID(Other);
}

bool UHandleBase::NotEqualName_Implementation(FName Other)
{
	return !EqualName(Other);
}

bool UHandleBase::IsHandleValid_Implementation()
{
	return HandleID.IsValid();
}

bool UHandleBase::IsHandleInValid_Implementation()
{
	return !IsHandleValid();
}

void UHandleBase::ClearHandle_Implementation()
{
	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		HandleManager->UnRegisterHandle(this);
	}
}
