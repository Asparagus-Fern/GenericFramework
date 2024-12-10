// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleSequence.h"

#include "LevelSequencePlayer.h"

bool UCBE_HandleSequence::CanExecuteButtonEvent_Implementation()
{
	return IsValid(Sequence);
}

void UCBE_HandleSequence::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (bIsAsync)
	{
	}
	else
	{
	}
}
