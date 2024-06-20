// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelSlot.h"
#include "LineSlot.generated.h"

class SLine;

/**
 * 
 */
UCLASS(MinimalAPI)
class ULineSlot : public UPanelSlot
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	void BuildSlot(TSharedRef<SLine> InLine);

private:
	TWeakPtr<SLine> MyLine;
};
