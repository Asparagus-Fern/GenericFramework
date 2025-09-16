// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Application/GraphicsSettingProxy.h"

#include "GameFramework/GameUserSettings.h"
#include "LocalPlayer/GenericLocalPlayerSettings.h"
#include "MVVM/PropertyViewModel.h"
#include "MVVM/Action/ActionPropertyValueViewModel.h"
#include "MVVM/Data/Multi/NumberPropertyValueViewModel.h"

#define LOCTEXT_NAMESPACE "FGenericSettingSystemModule"

void UGraphicsSettingProxy::GeneratePropertyListItemObjects_Implementation(TArray<UPropertyViewModel*>& Result)
{
	Super::GeneratePropertyListItemObjects_Implementation(Result);

	{
		UActionPropertyValueViewModel* ActionPropertyValueViewModel = NewObject<UActionPropertyValueViewModel>(this);
		ActionPropertyValueViewModel->SetPropertyName(TEXT("AutoSetQuality"));
		ActionPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("AutoSetQuality_DisplayName", "Auto-Set Quality"));
		ActionPropertyValueViewModel->SetPropertyDescription(LOCTEXT("AutoSetQuality_Description", "Automatically configure the graphics quality options based on a benchmark of the hardware."));
		ActionPropertyValueViewModel->SetIsDirtyProxy(true);
		ActionPropertyValueViewModel->SetActionText(LOCTEXT("AutoSetQuality_ActionDisplayName", "Auto-Set"));
		ActionPropertyValueViewModel->SetAction([](UActionPropertyValueViewModel* InActionViewModel)
			{
				GEngine->GetGameUserSettings()->RunHardwareBenchmark();
				GEngine->GetGameUserSettings()->ApplyHardwareBenchmarkResults();
			}
		);

		Result.Add(ActionPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("GraphicsQualityPresets"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("GraphicsQualityPresets_DisplayName", "Quality Presets"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("GraphicsQualityPresets_Description", "Quality Preset allows you to adjust multiple video options at once. Try a few options to see what fits your preference and device's performance."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetOverallScalabilityLevel, SetOverallScalabilityLevel));
		MultiPropertyValueViewModel->SetIsDirtyProxy(true);
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(-1,LOCTEXT("GraphicsQualityPresetsCustom", "Custom"));
		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("GraphicsQualityPresetsLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("GraphicsQualityPresetsMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("GraphicsQualityPresetsHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("GraphicsQualityPresetsEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("GraphicsQualityPresetsCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("ViewDistanceQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("ViewDistanceQuality_DisplayName", "View Distance Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("ViewDistanceQuality_Description", "View distance determines how far away objects are culled for performance."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetViewDistanceQuality, SetViewDistanceQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("ViewDistanceQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("ViewDistanceQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("ViewDistanceQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("ViewDistanceQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("ViewDistanceQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("ShadowQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("ShadowQuality_DisplayName", "Shadow Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("ShadowQuality_Description", "Shadow quality determines the resolution and view distance of dynamic shadows. Shadows improve visual quality and give better depth perception, but can reduce performance."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetShadowQuality, SetShadowQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("ShadowQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("ShadowQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("ShadowQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("ShadowQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("ShadowQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("GlobalIlluminationQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("GlobalIlluminationQuality_DisplayName", "Global Illumination Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("GlobalIlluminationQuality_Description", "Global Illumination controls the quality of dynamically calculated indirect lighting bounces, sky shadowing and Ambient Occlusion. Settings of 'High' and above use more accurate ray tracing methods to solve lighting, but can reduce performance."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetGlobalIlluminationQuality, SetGlobalIlluminationQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("GlobalIlluminationQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("GlobalIlluminationQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("GlobalIlluminationQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("GlobalIlluminationQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("GlobalIlluminationQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("ReflectionQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("ReflectionQuality_DisplayName", "Reflection Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("ReflectionQuality_Description", "Reflection quality determines the resolution and accuracy of reflections.  Settings of 'High' and above use more accurate ray tracing methods to solve reflections, but can reduce performance."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetReflectionQuality, SetReflectionQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("ReflectionQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("ReflectionQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("ReflectionQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("ReflectionQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("ReflectionQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("AntiAliasingQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("AntiAliasingQuality_DisplayName", "AntiAliasing Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("AntiAliasingQuality_Description", "Anti-Aliasing reduces jaggy artifacts along geometry edges. Increasing this setting will make edges look smoother, but can reduce performance. Higher settings mean more anti-aliasing."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetAntiAliasingQuality, SetAntiAliasingQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("AntiAliasingQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("AntiAliasingQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("AntiAliasingQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("AntiAliasingQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("AntiAliasingQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("TextureQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("TextureQuality_DisplayName", "Texture Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("TextureQuality_Description", "Texture quality determines the resolution of textures in game. Increasing this setting will make objects more detailed, but can reduce performance."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetTextureQuality, SetTextureQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("TextureQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("TextureQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("TextureQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("TextureQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("TextureQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("VisualEffectQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("VisualEffectQuality_DisplayName", "Visual Effect Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("VisualEffectQuality_Description", "Effects determines the quality of visual effects and lighting in game. Increasing this setting will increase the quality of visual effects, but can reduce performance."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetVisualEffectQuality, SetVisualEffectQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("VisualEffectQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("VisualEffectQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("VisualEffectQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("VisualEffectQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("VisualEffectQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("PostProcessingQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("PostProcessingQuality_DisplayName", "Post Processing Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("PostProcessingQuality_Description", "Post Processing effects include Motion Blur, Depth of Field and Bloom. Increasing this setting improves the quality of post process effects, but can reduce performance."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetPostProcessingQuality, SetPostProcessingQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("PostProcessingQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("PostProcessingQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("PostProcessingQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("PostProcessingQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("PostProcessingQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UNumberPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UNumberPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("FoliageQuality"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("FoliageQuality_DisplayName", "Foliage Quality"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("FoliageQuality_Description", "Foliage quality determines the resolution of foliage in game."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetFoliageQuality, SetFoliageQuality));
		MultiPropertyValueViewModel->SetIsAutoApplyProperty(true);

		MultiPropertyValueViewModel->AddNumberValue(0,LOCTEXT("FoliageQualityLow", "Low"));
		MultiPropertyValueViewModel->AddNumberValue(1,LOCTEXT("FoliageQualityMedium", "Medium"));
		MultiPropertyValueViewModel->AddNumberValue(2,LOCTEXT("FoliageQualityHigh", "High"));
		MultiPropertyValueViewModel->AddNumberValue(3,LOCTEXT("FoliageQualityEpic", "Epic"));
		MultiPropertyValueViewModel->AddNumberValue(4,LOCTEXT("FoliageQualityCinematic", "Cinematic"));

		Result.Add(MultiPropertyValueViewModel);
	}
}

#undef LOCTEXT_NAMESPACE
