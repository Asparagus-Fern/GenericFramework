// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Property/SessionSettingDataSourceCollection.h"

#include "DataSource/PropertyDataSource.h"
#include "MVVM/Data/Multi/BoolPropertyValueViewModel.h"
#include "MVVM/Data/Scalar/ScalarPropertyValueViewModel.h"

#define LOCTEXT_NAMESPACE "FGenericNetworkFrameworkModule"

#define GET_SESSION_SETTING_DATA_SOURCE(PropertyName) \
UPropertyDataSource::Create \
	( \
		this, \
		TArray<FString> \
		{ \
			GET_FUNCTION_NAME_STRING_CHECKED(USessionSettingDataSourceCollection, SessionSettings), \
			GET_FUNCTION_NAME_STRING_CHECKED(FGenericSessionSettings, PropertyName), \
		}, \
		TArray<FString>{ \
			GET_FUNCTION_NAME_STRING_CHECKED(USessionSettingDataSourceCollection, SessionSettings), \
			GET_FUNCTION_NAME_STRING_CHECKED(FGenericSessionSettings, PropertyName), \
		} \
	)

void USessionSettingDataSourceCollection::GeneratePropertyViewModels_Implementation(TArray<UPropertyViewModel*>& Result)
{
	Super::GeneratePropertyViewModels_Implementation(Result);

	{
		UScalarPropertyValueViewModel* ScalarPropertyValueViewModel = NewObject<UScalarPropertyValueViewModel>(this);
		ScalarPropertyValueViewModel->SetPropertyName(TEXT("NumPublicConnections"));
		ScalarPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("NumPublicConnections_DisplayName", "Num Public Connections"));
		ScalarPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(NumPublicConnections));

		Result.Add(ScalarPropertyValueViewModel);
	}

	{
		UScalarPropertyValueViewModel* ScalarPropertyValueViewModel = NewObject<UScalarPropertyValueViewModel>(this);
		ScalarPropertyValueViewModel->SetPropertyName(TEXT("NumPrivateConnections"));
		ScalarPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("NumPrivateConnections_DisplayName", "Num Private Connections"));
		ScalarPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(NumPrivateConnections));

		Result.Add(ScalarPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("ShouldAdvertise"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("ShouldAdvertise_DisplayName", "Should Advertise"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bShouldAdvertise));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("AllowJoinInProgress"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("AllowJoinInProgress_DisplayName", "Allow Join In Progress"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bAllowJoinInProgress));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("IsLANMatch"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("IsLANMatch_DisplayName", "Is LAN Match"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bIsLANMatch));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("IsDedicated"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("IsDedicated_DisplayName", "Is Dedicated"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bIsDedicated));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("UsesStats"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("UsesStats_DisplayName", "Uses Stats"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bUsesStats));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("AllowInvites"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("AllowInvites_DisplayName", "Allow Invites"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bAllowInvites));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("UsesPresence"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("UsesPresence_DisplayName", "Uses Presence"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bUsesPresence));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("AllowJoinViaPresence"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("AllowJoinViaPresence_DisplayName", "Allow Join Via Presence"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bAllowJoinViaPresence));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("AllowJoinViaPresenceFriendsOnly"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("AllowJoinViaPresenceFriendsOnly_DisplayName", "Allow Join Via Presence Friends Only"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bAllowJoinViaPresenceFriendsOnly));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("AntiCheatProtected"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("AntiCheatProtected_DisplayName", "Anti Cheat Protected"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bAntiCheatProtected));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("UseLobbiesIfAvailable"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("UseLobbiesIfAvailable_DisplayName", "Use Lobbies If Available"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bUseLobbiesIfAvailable));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}

	{
		UBoolPropertyValueViewModel* BoolPropertyValueViewModel = NewObject<UBoolPropertyValueViewModel>(this);
		BoolPropertyValueViewModel->SetPropertyName(TEXT("UseLobbiesVoiceChatIfAvailable"));
		BoolPropertyValueViewModel->SetPropertyDisplayName(LOCTEXT("UseLobbiesVoiceChatIfAvailable_DisplayName", "Use Lobbies Voice Chat If Available"));
		BoolPropertyValueViewModel->SetPropertyDataSource(GET_SESSION_SETTING_DATA_SOURCE(bUseLobbiesVoiceChatIfAvailable));

		BoolPropertyValueViewModel->SetTrueText(FText::FromString("Enable"));
		BoolPropertyValueViewModel->SetFalseText(FText::FromString("Disable"));

		Result.Add(BoolPropertyValueViewModel);
	}
}

void USessionSettingDataSourceCollection::OnPropertyApplied_Implementation(UPropertyViewModel* InPropertyViewModel)
{
	Super::OnPropertyApplied_Implementation(InPropertyViewModel);
}

void USessionSettingDataSourceCollection::OnPropertyReset_Implementation(UPropertyViewModel* InPropertyViewModel)
{
	Super::OnPropertyReset_Implementation(InPropertyViewModel);
}

void USessionSettingDataSourceCollection::SetSessionSettings(const FGenericSessionSettings& InSettings)
{
	SessionSettings = InSettings;
}

#undef GET_SESSION_SETTING_DATA_SOURCE

#undef LOCTEXT_NAMESPACE
