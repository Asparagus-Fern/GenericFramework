// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaHandle.h"

#include "IMediaModule.h"
#include "MediaPlayer.h"
#include "MediaPlaylist.h"
#include "Handle/HandleManager.h"
#include "Manager/ManagerStatics.h"

UMediaHandle* UMediaHandle::Register(FName HandleName)
{
	UMediaHandle* NewHandle = nullptr;
	if (UHandleManager* HandleManager = GetManager<UHandleManager>())
	{
		NewHandle = HandleManager->RegisterHandle<UMediaHandle>(HandleName);
	}
	return NewHandle;
}
