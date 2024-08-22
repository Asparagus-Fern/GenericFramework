// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CommonButtonHandle.h"

#include "DBTweenFloat.h"
#include "ScreenWidgetManager.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Manager/ManagerGlobal.h"

void UCommonButtonHandle::UpdateHandle(FSimpleMulticastDelegate OnFinish)
{
	if (GetIsAsync())
	{
		OnHandleFinishDelegate = OnFinish;

		UDBTweenFloat* DBTweenFloat = UDBTweenFloat::DOFloat("", Duration, 0.f, 1.f, EaseType, bIsLoop);
		DBTweenFloat->OnUpdate.AddDynamic(this, &UCommonButtonHandle::OnHandleUpdate);
		DBTweenFloat->OnComplete.AddDynamic(this, &UCommonButtonHandle::OnHandleFinish);
	}
	else
	{
		OnHandleUpdate(1.f);
		OnHandleFinish(1.f);
	}
}

bool UCommonButtonHandle::GetIsAsync()
{
	return bIsAsync;
}

void UCommonButtonHandle::OnHandleUpdate(float InValue)
{
}

void UCommonButtonHandle::OnHandleFinish(float InValue)
{
	OnHandleFinishDelegate.Broadcast();
}

void UScalarParameterHandle::UpdateHandle(FSimpleMulticastDelegate OnFinish)
{
	// UKismetMaterialLibrary::SetScalarParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, StartValue);
	Super::UpdateHandle(OnFinish);
}

void UScalarParameterHandle::OnHandleUpdate(float InValue)
{
	Super::OnHandleUpdate(InValue);
	// UKismetMaterialLibrary::SetScalarParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, FMath::Lerp(StartValue, EndValue, InValue));
}

void UVectorParameterHandle::UpdateHandle(FSimpleMulticastDelegate OnFinish)
{
	// UKismetMaterialLibrary::SetVectorParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, StartValue);
	Super::UpdateHandle(OnFinish);
}

void UVectorParameterHandle::OnHandleUpdate(float InValue)
{
	Super::OnHandleUpdate(InValue);
	// UKismetMaterialLibrary::SetVectorParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, FMath::Lerp(StartValue, EndValue, InValue));
}
