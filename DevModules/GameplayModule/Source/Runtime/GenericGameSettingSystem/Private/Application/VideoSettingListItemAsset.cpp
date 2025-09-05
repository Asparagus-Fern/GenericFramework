// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Application/VideoSettingListItemAsset.h"

#include "GameFramework/GameUserSettings.h"
#include "MVVM/Multi/MultiPropertyValueViewModel.h"
#include "StaticFunctions/StaticFunctions_Enum.h"
#include "UMG/PropertyListItem.h"

#define LOCTEXT_NAMESPACE "FGenericSettingSystemModule"

void UVideoSettingListItemAsset::GeneratePropertyListItemObjects(TArray<UPropertyListItemObject*>& Result)
{
	Super::GeneratePropertyListItemObjects(Result);

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetDisplayModeOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetFullscreenMode(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::ConvertIntToWindowMode(SelectedIndex)); }));

		NewItemObject->PropertyName = TEXT("DisplayMode");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "DisplayMode");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetOverallScalabilityLevel(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetOverallScalabilityLevel(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("OverallScalabilityLevel");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "OverallScalabilityLevel");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetViewDistanceQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetViewDistanceQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("ViewDistanceQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "ViewDistanceQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetShadowQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetShadowQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("ShadowQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "ShadowQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetGlobalIlluminationQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetGlobalIlluminationQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("GlobalIlluminationQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "GlobalIlluminationQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetReflectionQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetReflectionQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("ReflectionQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "ReflectionQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetAntiAliasingQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetAntiAliasingQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("AntiAliasingQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "AntiAliasingQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetTextureQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetTextureQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("TextureQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "TextureQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetVisualEffectQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetVisualEffectQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("VisualEffectQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "VisualEffectQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetPostProcessingQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetPostProcessingQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("PostProcessingQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "PostProcessingQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetFoliageQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetFoliageQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("FoliageQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "FoliageQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}

	{
		UPropertyListItemObject* NewItemObject = NewObject<UPropertyListItemObject>(this);
		UMultiPropertyValueViewModel* NewMultiPropertyViewModel = NewObject<UMultiPropertyValueViewModel>(NewItemObject);

		for (const auto& Option : GetQualityOptions())
		{
			USinglePropertyValueViewModel* NewSinglePropertyViewModel = NewObject<USinglePropertyValueViewModel>(NewMultiPropertyViewModel);
			NewSinglePropertyViewModel->PropertyValueName = Option.Key;
			NewSinglePropertyViewModel->PropertyValueDisplayName = Option.Value;
			NewMultiPropertyViewModel->AddValue(NewSinglePropertyViewModel);
		}

		NewMultiPropertyViewModel->SetPropertyValueGetter(FMultiPropertyValueGetter::CreateLambda([]() { return GEngine->GetGameUserSettings()->GetShadingQuality(); }));
		NewMultiPropertyViewModel->SetPropertyValueSetter(FMultiPropertyValueSetter::CreateLambda([](int32 SelectedIndex) { GEngine->GetGameUserSettings()->SetShadingQuality(SelectedIndex); }));

		NewItemObject->PropertyName = TEXT("ShadingQuality");
		NewItemObject->PropertyDisplayName = LOCTEXT("VideoSetting_DisplayName", "ShadingQuality");
		NewItemObject->PropertyValueViewModel = NewMultiPropertyViewModel;

		Result.Add(NewItemObject);
	}
}

TMap<FName, FText> UVideoSettingListItemAsset::GetDisplayModeOptions()
{
	const TMap<FName, FText> Options =
	{
		{TEXT("Fullscreen"), LOCTEXT("VideoSetting_DisplayModeOption", "Fullscreen")},
		{TEXT("WindowedFullscreen"), LOCTEXT("VideoSetting_DisplayModeOption", "WindowedFullscreen")},
		{TEXT("Windowed"), LOCTEXT("VideoSetting_DisplayModeOption", "Windowed")},
	};

	return Options;
}

TMap<FName, FText> UVideoSettingListItemAsset::GetQualityOptions()
{
	const TMap<FName, FText> Options =
	{
		{TEXT("QualityLow"), LOCTEXT("VideoSetting_QualityOption", "Low")},
		{TEXT("QualityMedium"), LOCTEXT("VideoSetting_QualityOption", "Medium")},
		{TEXT("QualityHigh"), LOCTEXT("VideoSetting_QualityOption", "High")},
		{TEXT("QualityEpic"), LOCTEXT("VideoSetting_QualityOption", "Epic")},
		{TEXT("QualityCinematic"), LOCTEXT("VideoSetting_QualityOption", "Cinematic")}
	};

	return Options;
}

#undef LOCTEXT_NAMESPACE
