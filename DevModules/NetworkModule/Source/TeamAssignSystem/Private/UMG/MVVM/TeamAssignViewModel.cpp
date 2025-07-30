// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/MVVM/TeamAssignViewModel.h"

bool UTeamAssignViewModel::GetIsEnableMidwayPlayerLogin() const
{
	return IsEnableMidwayPlayerLogin;
}

void UTeamAssignViewModel::SetIsEnableMidwayPlayerLogin(bool IsEnable)
{
	if (IsEnableMidwayPlayerLogin != IsEnable)
	{
		IsEnableMidwayPlayerLogin = IsEnable;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsEnableMidwayPlayerLogin);
	}
}

bool UTeamAssignViewModel::GetIsAutoFinishAssignTeam() const
{
	return IsAutoFinishAssignTeam;
}

void UTeamAssignViewModel::SetIsAutoFinishAssignTeam(bool IsAutoFinish)
{
	if (IsAutoFinishAssignTeam != IsAutoFinish)
	{
		IsAutoFinishAssignTeam = IsAutoFinish;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(IsAutoFinishAssignTeam);
	}
}

int32 UTeamAssignViewModel::GetTeamCount() const
{
	return TeamCount;
}

void UTeamAssignViewModel::SetTeamCount(int32 InTeamCount)
{
	if (TeamCount != InTeamCount)
	{
		TeamCount = InTeamCount;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(TeamCount);
	}
}
