// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaPlayManager.h"

#define LOCTEXT_NAMESPACE "UMediaPlayManager"

FText UMediaPlayManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Media Play Manager");
}

void UMediaPlayManager::NativeOnActived()
{
	Super::NativeOnActived();
}

void UMediaPlayManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}

#undef LOCTEXT_NAMESPACE
