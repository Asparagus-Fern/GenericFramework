// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "PropertyPanel.generated.h"

class UPropertyCollection;
class UPropertyListView;
class UPropertySourceHandle;
class UPropertySourceData;
class UPropertyDetailDescriptionPanel;
class UPropertyDetailPanel;

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyPanel : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif

public:
	virtual void SetupProperty();
	virtual void ClearupProperty();
	void RefreshProperty();

protected:
	virtual void RefreshPropertyWidget();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPropertySourceHandle> PropertySource;

	UPROPERTY(BlueprintReadOnly)
	UPropertyCollection* PropertyCollection = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UPropertyDetailPanel> Panel_ProertyDetail;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UPropertyDetailDescriptionPanel> Panel_ProertyDetailDescription;
};
