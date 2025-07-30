// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "PropertyListView.generated.h"

class UPropertyVisualData;

/**
 * 
 */
UCLASS(MinimalAPI, meta = (EntryClass = PropertyListEntryBase))
class UPropertyListView : public UListView
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif

public:
	PROPERTYPATHSYSTEM_API void SetVisualDataOverride(UPropertyVisualData* InVisualData);

protected:
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	virtual bool OnIsSelectableOrNavigableInternal(UObject* FirstSelectedItem) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPropertyVisualData> VisualData;
};
