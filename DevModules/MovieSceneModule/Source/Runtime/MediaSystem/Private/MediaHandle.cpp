// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaHandle.h"

#include "IMediaModule.h"
#include "MediaPlayer.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

UMediaHandle* UMediaHandle::Register(FName HandleName)
{
	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		return HandleManager->RegisterHandle<UMediaHandle>(HandleName);
	}
	return nullptr;
}
