// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnManager.h"

#define LOCTEXT_NAMESPACE "UPawnManager"

UPawnManager::UPawnManager()
{
}

FText UPawnManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Pawn Manager");
}

#undef LOCTEXT_NAMESPACE
