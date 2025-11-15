// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "SessionSearchPanel.generated.h"

class USessionSearchResultViewModel;
class USessionSearchSettingViewModel;
class USessionSearchList;

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API USessionSearchPanel : public UGenericWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif

protected:
	UFUNCTION(BlueprintCallable)
	void RefreshSessionSearchList();

	UFUNCTION(BlueprintNativeEvent)
	void OnFindSessionsStart();

	UFUNCTION(BlueprintNativeEvent)
	void OnFindSessionsComplete(bool bWasSuccessful);

public:
	UFUNCTION(BlueprintCallable)
	void SetSessionSearchSettingsViewModel(USessionSearchSettingViewModel* InViewModel);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<USessionSearchSettingViewModel> SessionSearchSettingsViewModelClass = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USessionSearchSettingViewModel> SessionSearchSettingsViewModel = nullptr;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USessionSearchList> SessionSearchList;
};
