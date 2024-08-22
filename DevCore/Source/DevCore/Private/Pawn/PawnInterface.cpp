// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnInterface.h"

IPawnInterface::IPawnInterface()
{
}

APawn* IPawnInterface::GetPawn()
{
	return Cast<APawn>(this);
}

FGameplayTag IPawnInterface::GetPawnTag()
{
	return FGameplayTag::EmptyTag;
}