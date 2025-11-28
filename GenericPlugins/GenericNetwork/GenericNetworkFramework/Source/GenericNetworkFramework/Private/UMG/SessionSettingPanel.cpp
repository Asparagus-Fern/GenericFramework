// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UMG/SessionSettingPanel.h"

#include "PropertySubsystem.h"
#include "Property/SessionSettingDataSourceCollection.h"
#include "UMG/PropertyCollection.h"

void USessionSettingPanel::NativeConstruct()
{
	Super::NativeConstruct();

	UPropertySubsystem::Delegate_OnPropertyProxyRegister.AddUObject(this, &USessionSettingPanel::OnPropertyProxyRegister);
	UPropertySubsystem::Delegate_OnPropertyProxyUnRegister.AddUObject(this, &USessionSettingPanel::OnPropertyProxyUnRegister);
}

void USessionSettingPanel::NativeDestruct()
{
	Super::NativeDestruct();

	UPropertySubsystem::Delegate_OnPropertyProxyRegister.RemoveAll(this);
	UPropertySubsystem::Delegate_OnPropertyProxyUnRegister.RemoveAll(this);
}

void USessionSettingPanel::OnPropertyProxyRegister(FGameplayTag InProxyTag, UPropertyProxy* InProxy)
{
	if (USessionSettingDataSourceCollection* SessionSettingDataSourceCollection = InProxy->GetPropertyDataSourceCollection<USessionSettingDataSourceCollection>())
	{
		SessionSettingProxies.Add(InProxy);
		RefreshSessionSettingDataSourceCollection();
	}
}

void USessionSettingPanel::OnPropertyProxyUnRegister(FGameplayTag InProxyTag, UPropertyProxy* InProxy)
{
	if (IsValid(InProxy->GetPropertyDataSourceCollection<USessionSettingDataSourceCollection>()))
	{
		SessionSettingProxies.Remove(InProxy);
	}
}

void USessionSettingPanel::RefreshSessionSettingDataSourceCollection()
{
	for (auto& SessionSettingProxy : SessionSettingProxies)
	{
		SessionSettingProxy->GetPropertyDataSourceCollection<USessionSettingDataSourceCollection>()->SetSessionSettings(SessionSettings);
	}
}

const FGenericSessionSettings& USessionSettingPanel::GetSessionSettings() const
{
	return SessionSettings;
}

void USessionSettingPanel::SetSessionSettings(const FGenericSessionSettings& InSessionSettings)
{
	SessionSettings = InSessionSettings;

	if (PropertyCollection_SessionSetting && SessionSettingCollectionAsset)
	{
		PropertyCollection_SessionSetting->SetPropertyCollectionAsset(SessionSettingCollectionAsset);
	}
}
