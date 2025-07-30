// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/MVVM/TeamInformation.h"

FText UTeamInformation::GetTeamDisplayName() const
{
	return TeamDisplayName;
}

void UTeamInformation::SetTeamDisplayName(FText InTeamDisplayName)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(TeamDisplayName, InTeamDisplayName))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(TeamDisplayName);
	}
}

int32 UTeamInformation::GetMinTeamPlayerCount() const
{
	return MinTeamPlayerCount;
}

void UTeamInformation::SetMinTeamPlayerCount(int32 InMinTeamPlayerCount)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MinTeamPlayerCount, InMinTeamPlayerCount))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(MinTeamPlayerCount);
	}
}

int32 UTeamInformation::GetMaxTeamPlayerCount() const
{
	return MaxTeamPlayerCount;
}

void UTeamInformation::SetMaxTeamPlayerCount(int32 InMaxTeamPlayerCount)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxTeamPlayerCount, InMaxTeamPlayerCount))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(MaxTeamPlayerCount);
	}
}
