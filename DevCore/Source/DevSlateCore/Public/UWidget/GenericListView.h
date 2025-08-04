// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "GenericListView.generated.h"

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UGenericListView : public UListView
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("GenericWidget", "Generic", "Generic Widget"); }
#endif
	
public:
	UFUNCTION(BlueprintCallable)
	void SetEntryWidgetClass(TSubclassOf<UUserWidget> InClass);
};
