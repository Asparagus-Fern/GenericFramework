// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/GameSettingSource.h"

#include "Collection/PropertyCollection.h"
#include "GameSetting/GameSettingCollection.h"
#include "Value/Action/PropertyActionValue.h"
#include "Value/Discrete/PropertyDiscreteValueDynamic_Enum.h"
#include "Value/Discrete/PropertyDiscreteValueDynamic_Number.h"

#define LOCTEXT_NAMESPACE "GameSetting"

void UGameSettingSource::InitializePropertyCollection(UPropertyCollection*& Collection)
{
	Collection->SetPropertyName(TEXT("GameSetting"));
	Collection->SetDisplayName(LOCTEXT("GameSetting_Name", "Settings"));
	Collection->SetDescriptionText(LOCTEXT("GameSetting_Description", "Adjust your game settings"));

	/* ==================== Controller ==================== */
	{
		UGameSettingCollection* Controller = NewObject<UGameSettingCollection>(Collection);
		Controller->SetPropertyName(TEXT("Controller"));
		Controller->SetDisplayName(LOCTEXT("Controller_Name", "Controller"));
		Controller->SetDescriptionText(LOCTEXT("Controller_Description", "Controller settings"));
		Collection->AddProperty(Controller);
	}

	/* ==================== Keyboard ==================== */
	{
		UGameSettingCollection* Keyboard = NewObject<UGameSettingCollection>(Collection);
		Keyboard->SetPropertyName(TEXT("Keyboard"));
		Keyboard->SetDisplayName(LOCTEXT("Keyboard_Name", "Keyboard"));
		Keyboard->SetDescriptionText(LOCTEXT("Keyboard_Description", "Keyboard settings"));
		Collection->AddProperty(Keyboard);
	}

	/* ==================== Game ==================== */
	{
		UGameSettingCollection* Game = NewObject<UGameSettingCollection>(Collection);
		Game->SetPropertyName(TEXT("Game"));
		Game->SetDisplayName(LOCTEXT("Game_Name", "Game"));
		Game->SetDescriptionText(LOCTEXT("Game_Description", "Game settings"));
		Collection->AddProperty(Game);
	}

	/* ==================== ViewAngle ==================== */
	{
		UGameSettingCollection* ViewAngle = NewObject<UGameSettingCollection>(Collection);
		ViewAngle->SetPropertyName(TEXT("ViewAngle"));
		ViewAngle->SetDisplayName(LOCTEXT("ViewAngle_Name", "ViewAngle"));
		ViewAngle->SetDescriptionText(LOCTEXT("ViewAngle_Description", "ViewAngle settings"));
		Collection->AddProperty(ViewAngle);
	}

	/* ==================== Language ==================== */
	{
		UGameSettingCollection* Language = NewObject<UGameSettingCollection>(Collection);
		Language->SetPropertyName(TEXT("Language"));
		Language->SetDisplayName(LOCTEXT("Language_Name", "Language"));
		Language->SetDescriptionText(LOCTEXT("Language_Description", "Language settings"));
		Collection->AddProperty(Language);
	}

	/* ==================== Display ==================== */
	{
		UGameSettingCollection* Display = NewObject<UGameSettingCollection>(Collection);
		Display->SetPropertyName(TEXT("Display"));
		Display->SetDisplayName(LOCTEXT("Display_Name", "Display"));
		Display->SetDescriptionText(LOCTEXT("Display_Description", "Display settings"));
		Collection->AddProperty(Display);
	}

	/* ==================== Vedio ==================== */
	{
		UGameSettingCollection* Vedio = NewObject<UGameSettingCollection>(Collection);
		Vedio->SetPropertyName(TEXT("Vedio"));
		Vedio->SetDisplayName(LOCTEXT("Vedio_Name", "Vedio"));
		Vedio->SetDescriptionText(LOCTEXT("Vedio_Description", "Vedio settings"));
		Collection->AddProperty(Vedio);

		{
			UPropertyActionValue* AutosetQuality = NewObject<UPropertyActionValue>(Vedio);
			AutosetQuality->SetPropertyName(TEXT("AutosetQuality"));
			AutosetQuality->SetDisplayName(LOCTEXT("AutosetQuality_Name", "AutosetQuality"));
			AutosetQuality->SetDescriptionText(LOCTEXT("AutosetQuality_Description", "Autoset Quality"));

			AutosetQuality->SetActionText(LOCTEXT("AutosetQuality_Action", "Auto-set"));
			Vedio->AddProperty(AutosetQuality);
		}
	}

	/* ==================== Audio ==================== */
	{
		UGameSettingCollection* Audio = NewObject<UGameSettingCollection>(Collection);
		Audio->SetPropertyName(TEXT("Audio"));
		Audio->SetDisplayName(LOCTEXT("Audio_Name", "Audio"));
		Audio->SetDescriptionText(LOCTEXT("Audio_Description", "Audio settings"));
		Collection->AddProperty(Audio);
	}

	/* ==================== AuxiliarySettings ==================== */
	{
		UGameSettingCollection* AuxiliarySettings = NewObject<UGameSettingCollection>(Collection);
		AuxiliarySettings->SetPropertyName(TEXT("AuxiliarySettings"));
		AuxiliarySettings->SetDisplayName(LOCTEXT("AuxiliarySettings_Name", "AuxiliarySettings"));
		AuxiliarySettings->SetDescriptionText(LOCTEXT("AuxiliarySettings_Description", "Auxiliary settings"));
		Collection->AddProperty(AuxiliarySettings);
	}
}

#undef LOCTEXT_NAMESPACE
