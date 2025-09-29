// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/VideoSettingProxy.h"

#include "DataSource/PropertyDataSource.h"
#include "GameFramework/GameUserSettings.h"
#include "LocalPlayer/GenericLocalPlayerSettings.h"
#include "MVVM/Data/Multi/BoolPropertyValueViewModel.h"
#include "MVVM/Data/Multi/EnumPropertyValueViewModel.h"

#define LOCTEXT_NAMESPACE "FGenericSettingSystemModule"

void UVideoSettingProxy::GeneratePropertyListItemObjects_Implementation(TArray<UPropertyViewModel*>& Result)
{
	Super::GeneratePropertyListItemObjects_Implementation(Result);

	{
		UEnumPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UEnumPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("WindowMode"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("WindowMode_DisplayName", "Window Mode"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("WindowMode_Description", "In Windowed mode you can interact with other windows more easily, and drag the edges of the window to set the size. In Windowed Fullscreen mode you can easily switch between applications. In Fullscreen mode you cannot interact with other windows as easily, but the game will run slightly faster."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(GetFullscreenMode, SetFullscreenMode));

		MultiPropertyValueViewModel->AddEnumValue(EWindowMode::Type::Fullscreen,LOCTEXT("WindowModeFullscreen", "Fullscreen"));
		MultiPropertyValueViewModel->AddEnumValue(EWindowMode::Type::WindowedFullscreen,LOCTEXT("WindowModeWindowedFullscreen", "Windowed Fullscreen"));
		MultiPropertyValueViewModel->AddEnumValue(EWindowMode::Type::Windowed,LOCTEXT("WindowModeWindowed", "Windowed"));

		Result.Add(MultiPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* MultiPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		MultiPropertyValueViewModel->SetPropertyName(TEXT("VSync"));
		MultiPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("VSync_DisplayName", "Vertical Sync"));
		MultiPropertyValueViewModel->SetPropertyDescription(LOCTEXT("VSync_Description", "Enabling Vertical Sync eliminates screen tearing by always rendering and presenting a full frame. Disabling Vertical Sync can give higher frame rate and better input response, but can result in horizontal screen tearing."));
		MultiPropertyValueViewModel->SetPropertyDataSource(GET_LOCAL_PLAYER_SETTINGS_DATA_SOURCE(IsVSyncEnabled, SetVSyncEnabled));

		MultiPropertyValueViewModel->SetFalseText(LOCTEXT("WindowModeFullscreen", "Off"));
		MultiPropertyValueViewModel->SetTrueText(LOCTEXT("WindowModeWindowedFullscreen", "On"));

		Result.Add(MultiPropertyValueViewModel);
	}

	// GEngine->GetGameUserSettings()->SetScreenResolution()
}

#undef LOCTEXT_NAMESPACE
