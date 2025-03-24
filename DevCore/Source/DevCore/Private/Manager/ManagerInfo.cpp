// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/ManagerInfo.h"

bool UManagerInfo::InitializeManagerInfo(IManagerInterface* InInterface)
{
	if (!InInterface)
	{
		return false;
	}

	ManagerInterface = InInterface;
	return true;
}