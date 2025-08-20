// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ViewModel/GameSettingViewModel.h"

#include "ViewModel/QualitySettingViewModel.h"

UGameSettingViewModel::UGameSettingViewModel(const FObjectInitializer& ObjectInitializer)
{
	QualitySettings = CreateDefaultSubobject<UQualitySettingViewModel>(TEXT("QualitySettings"));
}

TArray<FString> UGameSettingViewModel::GetQualityStringName()
{
	TArray<FString> QualityStringNames;
	QualityStringNames.Add(TEXT("Low"));
	QualityStringNames.Add(TEXT("Medium"));
	QualityStringNames.Add(TEXT("High"));
	QualityStringNames.Add(TEXT("Epic"));
	QualityStringNames.Add(TEXT("Cinematic"));
	return QualityStringNames;
}
