// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonButtonEvent/TimelineButtonEvent/TBE_HandleMaterialVectorParameter.h"

#include "ScreenWidgetManager.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Manager/ManagerProxy.h"
#include "Materials/MaterialParameterCollection.h"

bool UTBE_HandleMaterialVectorParameter::CanExecuteButtonEvent_Implementation()
{
	return IsValid(Collection) && !ParameterName.IsNone();
}

void UTBE_HandleMaterialVectorParameter::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();
	UKismetMaterialLibrary::SetVectorParameterValue(UManagerProxy::Get()->GetManager<UScreenWidgetManager>(), Collection, ParameterName, Value);

	if (bIsAsync)
	{
		MarkAsActivedFinish();
	}
}

void UTBE_HandleMaterialVectorParameter::HandleTimelineUpdate_Implementation(float Alpha)
{
	UKismetMaterialLibrary::SetVectorParameterValue(UManagerProxy::Get()->GetManager<UScreenWidgetManager>(), Collection, ParameterName, FMath::Lerp(StartValue, EndValue, Alpha));
}
