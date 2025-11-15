// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "UMG/SessionSearchPanel.h"

#include "GenericSessionSubsystem.h"
#include "WidgetType.h"
#include "UMG/SessionSearchList.h"
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
		GenericSessionSubsystem->FindSessions(FUniqueNetworkID(GetOwningPlayer()), SessionSearchSettingsViewModel->GetSessionSettings(), FOnFindSessionsCompleteDelegate::CreateUFunction(this,GET_FUNCTION_NAME_CHECKED(USessionSearchPanel, OnFindSessionsComplete)));
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
		TArray<USessionSearchResultViewModel*> Results;
		SessionSearchSettingsViewModel->RefreshSessionSearchResults();
		SessionSearchSettingsViewModel->GetSessionSearchResults(Results);

		SessionSearchList->SetSessionSearchResult(Results);
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
