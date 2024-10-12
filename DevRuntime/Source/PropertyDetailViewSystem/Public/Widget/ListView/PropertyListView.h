// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "PropertyListView.generated.h"

class UPropertyVisualData;

/**
 * 
 */
UCLASS(meta = (EntryClass = PropertyListEntryBase))
class PROPERTYDETAILVIEWSYSTEM_API UPropertyListView : public UListView
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif

protected:
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	virtual bool OnIsSelectableOrNavigableInternal(UObject* FirstSelectedItem) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPropertyVisualData> VisualData;
};
