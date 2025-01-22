// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"

#include "PropertyDetailPanel.generated.h"

class UPropertyCollection;
class UTextBlock;
class UPropertyListView;

/**
 * 属性细节面板
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDetailPanel : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	void UpdatePropertyDetail(UPropertyCollection* InPropertyCollection);

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_Title;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Text_TitleDescription;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UPropertyListView> ListView_Property;
};
