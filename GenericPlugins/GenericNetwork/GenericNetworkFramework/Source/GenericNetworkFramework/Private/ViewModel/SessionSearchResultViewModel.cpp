// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "ViewModel/SessionSearchResultViewModel.h"

#include "ViewModel/SessionSettingsViewModel.h"

void USessionSearchResultViewModel::Initialize(const FOnlineSessionSearchResult& InResult)
{
	check(InResult.IsValid())
	Result = InResult;

	SetPingInMs(Result.PingInMs);
	SetUniqueIdRepl(Result.Session.OwningUserId);
	SetOwningUserName(Result.Session.OwningUserName);

	USessionSettingsViewModel* NewViewModel = NewObject<USessionSettingsViewModel>(this);
	NewViewModel->Initialize(Result.Session.SessionSettings);
	SetSessionSettings(NewViewModel);

	SetNumOpenPrivateConnections(Result.Session.NumOpenPrivateConnections);
	SetNumOpenPublicConnections(Result.Session.NumOpenPublicConnections);
}

int32 USessionSearchResultViewModel::GetPingInMs() const
{
	return PingInMs;
}

void USessionSearchResultViewModel::SetPingInMs(int32 InValue)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(PingInMs, InValue);
}

const FUniqueNetIdRepl& USessionSearchResultViewModel::GetUniqueIdRepl() const
{
	return UniqueIdRepl;
}

void USessionSearchResultViewModel::SetUniqueIdRepl(const FUniqueNetIdRepl& InValue)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(UniqueIdRepl, InValue);
}

FString USessionSearchResultViewModel::GetOwningUserName() const
{
	return OwningUserName;
}

void USessionSearchResultViewModel::SetOwningUserName(FString InValue)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(OwningUserName, InValue);
}

USessionSettingsViewModel* USessionSearchResultViewModel::GetSessionSettings() const
{
	return SessionSettings;
}

void USessionSearchResultViewModel::SetSessionSettings(USessionSettingsViewModel* InValue)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(SessionSettings, InValue);
}

int32 USessionSearchResultViewModel::GetNumOpenPrivateConnections() const
{
	return NumOpenPrivateConnections;
}

void USessionSearchResultViewModel::SetNumOpenPrivateConnections(int32 InValue)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(NumOpenPrivateConnections, InValue);
}

int32 USessionSearchResultViewModel::GetNumOpenPublicConnections() const
{
	return NumOpenPublicConnections;
}

void USessionSearchResultViewModel::SetNumOpenPublicConnections(int32 InValue)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(NumOpenPublicConnections, InValue);
}
