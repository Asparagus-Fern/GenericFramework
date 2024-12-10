// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceType.h"

FLevelSequenceHandle::FLevelSequenceHandle()
{
}

FLevelSequenceHandle::FLevelSequenceHandle(FName InHandleID, ALevelSequenceActor* InLevelSequenceActor, ULevelSequencePlayer* InLevelSequencePlayer)
	: HandleID(InHandleID),
	  LevelSequenceActor(InLevelSequenceActor),
	  LevelSequencePlayer(InLevelSequencePlayer)
{
}
