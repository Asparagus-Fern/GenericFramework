// Fill out your copyright notice in the Description page of Project Settings.


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