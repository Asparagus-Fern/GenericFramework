// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ViewModel/QualitySettingViewModel.h"

#include "GameFramework/GameUserSettings.h"

#define LOCTEXT_NAMESPACE "FGameplayModule"

FText UQualitySettingViewModel::GetOverallScalabilityLevel() const
{
	return ConvertToQualityText(GEngine->GetGameUserSettings()->GetOverallScalabilityLevel());
}

void UQualitySettingViewModel::SetOverallScalabilityLevel(int32 InQuality)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(OverallScalabilityLevel, InQuality);
	GEngine->GetGameUserSettings()->SetOverallScalabilityLevel(InQuality);
}

FText UQualitySettingViewModel::GetViewDistanceQuality() const
{
	return ConvertToQualityText(GEngine->GetGameUserSettings()->GetViewDistanceQuality());
}

void UQualitySettingViewModel::SetViewDistanceQuality(int32 InQuality)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(ViewDistanceQuality, InQuality);
	GEngine->GetGameUserSettings()->SetViewDistanceQuality(InQuality);
}

FText UQualitySettingViewModel::ConvertToQualityText(int32 InQuality) const
{
	switch (InQuality)
	{
	case 0:
		return LOCTEXT("Quality0", "Low");
	case 1:
		return LOCTEXT("Quality1", "Medium");
	case 2:
		return LOCTEXT("Quality2", "High");
	case 3:
		return LOCTEXT("Quality3", "Epic");
	case 4:
		return LOCTEXT("Quality4", "Cinematic");
	default:
		return LOCTEXT("QualityUnknown", "Unknown");
	}
}

#undef LOCTEXT_NAMESPACE
