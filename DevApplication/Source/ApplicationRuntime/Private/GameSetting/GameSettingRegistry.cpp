// Fill out your copyright notice in the Description page of Project Settings.
#include "GameSetting/GameSettingRegistry.h"

#include "Collection/PropertyCollection.h"
#include "DataSource/PropertyDataSouceDynamic.h"
#include "GameSetting/GameSettingCollection.h"
#include "GameSetting/GameSettings.h"
#include "Value/Action/PropertyActionValue.h"
#include "Value/Discrete/PropertyDiscreteValueDynamic_Bool.h"
#include "Value/Discrete/PropertyDiscreteValueDynamic_Enum.h"
#include "Value/Discrete/PropertyDiscreteValueDynamic_Number.h"
#include "Value/Scalar/PropertyScalarValueDynamic.h"

#define LOCTEXT_NAMESPACE "GameSetting"

void UGameSettingRegistry::Initialize()
{
	if (IsValid(Collection))
	{
		return;
	}

	Collection = NewObject<UPropertyCollection>(this);
	Collection->SetPropertyName(TEXT("GameSetting"));
	Collection->SetDisplayName(LOCTEXT("GameSetting_Name", "Settings"));
	Collection->SetDescriptionText(LOCTEXT("GameSetting_Description", "Adjust your game settings"));

	Collection->SetPropertyContext(UGameSettings::Get());
	Collection->Initialize();

	/* ==================== Controller ==================== */
	{
		UGameSettingCollection* Controller = NewObject<UGameSettingCollection>(Collection);
		Controller->SetPropertyName(TEXT("Controller"));
		Controller->SetDisplayName(LOCTEXT("Controller_Name", "Controller"));
		Controller->SetDescriptionText(LOCTEXT("Controller_Description", "Controller settings"));
		Collection->AddProperty(Controller);


		{
			UPropertyActionValue* Test1 = NewObject<UPropertyActionValue>(Controller);
			Test1->SetPropertyName(TEXT("Test1"));
			Test1->SetDisplayName(LOCTEXT("Test1_Name", "Test1"));
			Test1->SetDescriptionText(LOCTEXT("Test1_Description", "Test1"));

			Test1->SetActionText(LOCTEXT("Test1_Action", "Test1"));
			Test1->SetAction(FOnExecutePropertyAction::CreateLambda([](UPropertyEntity*)
					{
						DPRINT(Log, TEXT("Execute Test1 Action"))
					}
				)
			);

			Controller->AddProperty(Test1);
		}

		{
			UPropertyScalarValueDynamic* Test2 = NewObject<UPropertyScalarValueDynamic>(Controller);
			Test2->SetPropertyName(TEXT("Test2"));
			Test2->SetDisplayName(LOCTEXT("Test2_Name", "Test2"));
			Test2->SetDescriptionText(LOCTEXT("Test2_Description", "Test2"));

			Test2->SetDataSourceGetter(GET_GAME_SETTINGS_FUNCTION_PATH(Test2));
			Test2->SetDataSourceSetter(GET_GAME_SETTINGS_FUNCTION_PATH(Test2));
			Test2->SetDisplayFormat(UPropertyScalarValueDynamic::FormatAsDigits(1, 2));

			Test2->SetSourceRange(TRange<double>(0, 100));
			Test2->SetSourceStep(0.0001);

			Test2->SetDefaultValue(0.5f);

			// Test2->SetMinimumLimit(0.25);
			// Test2->SetMaximumLimit(0.75);

			Controller->AddProperty(Test2);
		}

		{
			UPropertyDiscreteValueDynamic_Bool* Test3 = NewObject<UPropertyDiscreteValueDynamic_Bool>(Controller);
			Test3->SetPropertyName(TEXT("Test3"));
			Test3->SetDisplayName(LOCTEXT("Test3_Name", "Test3"));
			Test3->SetDescriptionText(LOCTEXT("Test3_Description", "Test3"));

			Test3->SetDataSourceGetter(GET_GAME_SETTINGS_FUNCTION_PATH(bTest3));
			Test3->SetDataSourceSetter(GET_GAME_SETTINGS_FUNCTION_PATH(bTest3));

			Controller->AddProperty(Test3);
		}

		{
			UPropertyDiscreteValueDynamic_Number* Test4 = NewObject<UPropertyDiscreteValueDynamic_Number>(Controller);
			Test4->SetPropertyName(TEXT("Test4"));
			Test4->SetDisplayName(LOCTEXT("Test4_Name", "Test4"));
			Test4->SetDescriptionText(LOCTEXT("Test4_Description", "Test4"));

			Test4->SetDataSourceGetter(GET_GAME_SETTINGS_FUNCTION_PATH(GetGlobalIlluminationQuality));
			Test4->SetDataSourceSetter(GET_GAME_SETTINGS_FUNCTION_PATH(SetGlobalIlluminationQuality));

			Test4->AddNumberOption(0, LOCTEXT("VisualEffectQualityLow", "Low"));
			Test4->AddNumberOption(1, LOCTEXT("VisualEffectQualityMedium", "Medium"));
			Test4->AddNumberOption(2, LOCTEXT("VisualEffectQualityHigh", "High"));
			Test4->AddNumberOption(3, LOCTEXT("VisualEffectQualityEpic", "Epic"));

			Controller->AddProperty(Test4);
		}

		DLOG(LogProperty, Warning, TEXT(""))
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

	RegisterProperty(Collection);
}

void UGameSettingRegistry::SavePropertyChanges()
{
	UGameSettings::Get()->SaveSettings();
}

#undef LOCTEXT_NAMESPACE
