// Fill out your copyright notice in the Description page of Project Settings.

#include "Manager/ManagerEdInterface.h"

IManagerEdInterface::IManagerEdInterface()
	: bEditorActived(false)
{
}

void IManagerEdInterface::NativeOnEditorActived()
{
	bEditorActived = true;
}

void IManagerEdInterface::NativeOnEditorInactived()
{
	bEditorActived = false;
}
