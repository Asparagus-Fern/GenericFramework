// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "Base/GenericWidget.h"
#include "SessionSettingPanel.generated.h"


class UPropertyCollectionAsset;
class UPropertyCollection;

/**
 * 
 */
UCLASS(MinimalAPI)
class USessionSettingPanel : public UGenericWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	virtual void OnPropertyProxyRegister(FGameplayTag InProxyTag, UPropertyProxy* InProxy);
	virtual void OnPropertyProxyUnRegister(FGameplayTag InProxyTag, UPropertyProxy* InProxy);
	virtual void RefreshSessionSettingDataSourceCollection();

public:
	UFUNCTION(BlueprintPure)
	const FGenericSessionSettings& GetSessionSettings() const;

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API void SetSessionSettings(const FGenericSessionSettings& InSessionSettings);

protected:
	UPROPERTY()
	FGenericSessionSettings SessionSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UPropertyCollectionAsset> SessionSettingCollectionAsset = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UPropertyProxy>> SessionSettingProxies;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyCollection> PropertyCollection_SessionSetting;
};
