// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "UMG/SessionSearchPanel.h"

#include "GenericSessionSubsystem.h"
#include "WidgetType.h"
#include "UMG/SessionSearchList.h"
#include "ViewModel/SessionSearchResultViewModel.h"
#include "ViewModel/SessionSearchSettingViewModel.h"

#if WITH_EDITOR
#include "Editor/WidgetCompilerLog.h"
#endif

void USessionSearchPanel::NativeConstruct()
{
	Super::NativeConstruct();
	RefreshSessionSearchList();
}

void USessionSearchPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

#if WITH_EDITOR

void USessionSearchPanel::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!SessionSearchSettingsViewModelClass)
	{
		CompileLog.Error(FText::FromString(TEXT("SessionSearchSettingsViewModelClass Is InValid")));
	}
}

#endif

void USessionSearchPanel::RefreshSessionSearchList()
{
	if (!SessionSearchSettingsViewModel)
	{
		if (SessionSearchSettingsViewModelClass)
		{
			SessionSearchSettingsViewModel = NewObject<USessionSearchSettingViewModel>(this, SessionSearchSettingsViewModelClass);
		}
		else
		{
			SessionSearchSettingsViewModel = NewObject<USessionSearchSettingViewModel>(this);
		}
	}

	OnFindSessionsStart();

	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(this))
	{
		SessionSearchSettingsViewModel->SessionSearchSettings.EncodeSessionSearchSettings();
		GenericSessionSubsystem->FindSessions(FUniqueNetworkID(GetOwningPlayer()), SessionSearchSettingsViewModel->GetSessionSearchSettings(), FOnFindSessionsCompleteDelegate::CreateUFunction(this,GET_FUNCTION_NAME_CHECKED(USessionSearchPanel, OnFindSessionsComplete)));
	}
}

void USessionSearchPanel::OnFindSessionsStart_Implementation()
{
	if (SessionSearchList)
	{
		SessionSearchList->OnFindSessionsStart();
	}
}

void USessionSearchPanel::OnFindSessionsComplete_Implementation(bool bWasSuccessful)
{
	if (SessionSearchList)
	{
		TSharedRef<FOnlineSessionSearch> SessionSearchSettings = SessionSearchSettingsViewModel->GetSessionSearchSettings();

		SessionSearchResultViewModels.Reset();
		for (auto& SearchResult : SessionSearchSettings->SearchResults)
		{
			USessionSearchResultViewModel* NewViewModel = NewObject<USessionSearchResultViewModel>(this);
			NewViewModel->SetSessionSearchResult(SearchResult);
			SessionSearchResultViewModels.Add(NewViewModel);
		}

		SessionSearchList->SetSessionSearchResult(SessionSearchResultViewModels);
		SessionSearchList->OnFindSessionsComplete();
	}
}

void USessionSearchPanel::SetSessionSearchSettingsViewModel(USessionSearchSettingViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(SessionSearchSettingsViewModel);

	SessionSearchSettingsViewModel = InViewModel;

	if (SessionSearchSettingsViewModel)
	{
		RefreshSessionSearchList();
	}
}
