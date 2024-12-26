// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreInternalManager.h"

FCoreInternalManager::FCoreInternalManager()
{
}

FCoreInternalManager::~FCoreInternalManager()
{
}

int32 FCoreInternalManager::GetManagerOrder()
{
	return IManagerInterface::GetManagerOrder();
}
