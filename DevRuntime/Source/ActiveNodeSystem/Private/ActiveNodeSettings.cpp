// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNodeSettings.h"

UActiveNodeSettings::UActiveNodeSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bAutoLogin(true)
	, bBlockUpdate(false)
{
	
}