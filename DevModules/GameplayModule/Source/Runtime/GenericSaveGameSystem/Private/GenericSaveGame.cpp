// Copyright ChenTaiye 2025. All Rights Reserved.


#include "GenericSaveGame.h"

void UGenericSaveGame::OnSaved()
{
	LastSaveTime = FDateTime::Now();
}

void UGenericSaveGame::OnLoaded()
{
	LastLoadTime = FDateTime::Now();
}

FDateTime UGenericSaveGame::GetLastSaveTime() const
{
	return LastSaveTime;
}

FDateTime UGenericSaveGame::GetLastLoadTime() const
{
	return LastLoadTime;
}
