// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonButtonEvent/TimelineButtonEvent/TBE_HandleMaterialScalarParameter.h"

#include "ScreenWidgetManager.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollection.h"

bool UTBE_HandleMaterialScalarParameter::CanExecuteButtonEvent_Implementation()
{
	return IsValid(Collection) && !ParameterName.IsNone();
}

void UTBE_HandleMaterialScalarParameter::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();
	UKismetMaterialLibrary::SetScalarParameterValue(GetManager<UScreenWidgetManager>(), Collection, ParameterName, Value);

	if (bIsAsync)
	{
		MarkAsActivedFinish();
	}
}

void UTBE_HandleMaterialScalarParameter::HandleTimelineUpdate_Implementation(float Alpha)
{
	UKismetMaterialLibrary::SetScalarParameterValue(GetManager<UScreenWidgetManager>(), Collection, ParameterName, FMath::Lerp(StartValue, EndValue, Alpha));
}
