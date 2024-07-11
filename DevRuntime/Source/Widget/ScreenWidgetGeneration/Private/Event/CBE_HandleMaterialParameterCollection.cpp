// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_HandleMaterialParameterCollection.h"

#include "DBTweenFloat.h"
#include "ScreenWidgetManager.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Manager/ManagerGlobal.h"

void UMaterialParameterHandle::UpdateParameter()
{
	if (bIsAsync)
	{
		UDBTweenFloat* DBTweenFloat = UDBTweenFloat::DOFloat("", Duration, 0.f, 1.f);
		DBTweenFloat->OnUpdate.AddDynamic(this, &UMaterialParameterHandle::AsyncUpdateParameter);
	}
}

void UMaterialParameterHandle::AsyncUpdateParameter(float InValue)
{
}

void UScalarParameterHandle::UpdateParameter()
{
	UMaterialParameterHandle::UpdateParameter();

	if (bIsAsync)
	{
		UKismetMaterialLibrary::SetScalarParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, StartValue);
	}
	else
	{
		UKismetMaterialLibrary::SetScalarParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, EndValue);
	}
}

void UScalarParameterHandle::AsyncUpdateParameter(float InValue)
{
	Super::AsyncUpdateParameter(InValue);
	UKismetMaterialLibrary::SetScalarParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, FMath::Lerp(StartValue, EndValue, InValue));
}

void UVectorParameterHandle::UpdateParameter()
{
	UMaterialParameterHandle::UpdateParameter();

	if (bIsAsync)
	{
		UKismetMaterialLibrary::SetVectorParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, StartValue);
	}
	else
	{
		UKismetMaterialLibrary::SetVectorParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, EndValue);
	}
}

void UVectorParameterHandle::AsyncUpdateParameter(float InValue)
{
	Super::AsyncUpdateParameter(InValue);
	UKismetMaterialLibrary::SetVectorParameterValue(GetManager<UScreenWidgetManager>()->GetWorld(), Collection, ParameterName, FMath::Lerp(StartValue, EndValue, InValue));
}

void UCBE_HandleMaterialParameterCollection::NativeOnActived()
{
	Super::NativeOnActived();

	for (const auto& ActiveScalarParameterHandle : ActiveScalarParameterHandles)
	{
		ActiveScalarParameterHandle->UpdateParameter();
	}

	for (const auto& ActiveVectorParameterHandle : ActiveVectorParameterHandles)
	{
		ActiveVectorParameterHandle->UpdateParameter();
	}
}

void UCBE_HandleMaterialParameterCollection::NativeOnInactived()
{
	Super::NativeOnInactived();

	for (const auto& ActiveScalarParameterHandle : InactiveScalarParameterHandles)
	{
		ActiveScalarParameterHandle->UpdateParameter();
	}

	for (const auto& ActiveVectorParameterHandle : InactiveVectorParameterHandles)
	{
		ActiveVectorParameterHandle->UpdateParameter();
	}
}
