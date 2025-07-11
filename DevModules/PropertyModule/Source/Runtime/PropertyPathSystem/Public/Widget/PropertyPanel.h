// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "PropertyPanel.generated.h"

class UPropertyRegistry;
class UPropertyCollection;
class UPropertyListView;
class UPropertySourceHandle;
class UPropertySourceData;
class UPropertyDetailDescriptionPanel;
class UPropertyDetailPanel;

/**
 * 
 */
UCLASS(Abstract)
class PROPERTYPATHSYSTEM_API UPropertyPanel : public UGenericWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif

public:
	/* 初始化属性面板 */
	virtual void SetupProperty();

	/* 清除属性面板 */
	virtual void ClearupProperty();

	/* 刷新属性面板 */
	void RefreshProperty();

	template <typename PropertyRegistryT = UPropertyRegistry>
	PropertyRegistryT* GetRegistry() const { return Cast<PropertyRegistryT>(Registry); }
	
protected:
	void SetPropertyCollection(UPropertyCollection* InCollection);

	/* 重载此函数自定义刷新 */
	virtual void Refresh();

	/* 刷新细节面板 */
	void RefreshPropertyWidget(UPropertyCollection* InCollection) const;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPropertyRegistry> PropertyRegistry;

	/* 当前面板的属性集 */
	UPROPERTY(BlueprintReadOnly)
	UPropertyCollection* Collection = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UPropertyRegistry> Registry;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UPropertyDetailPanel> Panel_ProertyDetail;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UPropertyDetailDescriptionPanel> Panel_ProertyDetailDescription;
};
