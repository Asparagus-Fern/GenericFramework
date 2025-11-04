// Copyright ChenTaiye 2025. All Rights Reserved.

#include "SaveGameType.h"

#include "GenericSaveGame.h"

DEFINE_LOG_CATEGORY(GenericLogSaveGame);

FSaveGameParameter::FSaveGameParameter()
{
}

bool FSaveGameParameter::CanSave() const
{
	return IsValid(SaveGame) && !SaveName.IsEmpty() && (UserIndex != INDEX_NONE);
}

bool FSaveGameParameter::CanLoad() const
{
	return !SaveName.IsEmpty() && (UserIndex != INDEX_NONE);
}

bool FSaveGameParameter::CheckIsValid() const
{
	return IsValid(SaveGame) && !SaveName.IsEmpty() && UserIndex != INDEX_NONE;
}

FString FSaveGameParameter::GetSaveGameSlotName() const
{
	return FString::FromInt(UserIndex) + TEXT("/") + SaveName;
}

void FSaveGameParameter::OnSuccess()
{
	OnSuccessEvent.Broadcast();
}

void FSaveGameParameter::OnFail()
{
	OnFailEvent.Broadcast();
}
