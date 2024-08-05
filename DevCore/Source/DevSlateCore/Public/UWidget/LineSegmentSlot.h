// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelSlot.h"
#include "LineSegmentSlot.generated.h"

class SLineSegment;

/**
 * 
 */
UCLASS(MinimalAPI)
class ULineSegmentSlot : public UPanelSlot
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	void BuildSlot(const TSharedRef<SLineSegment>& InLineSegment);

private:
	TWeakPtr<SLineSegment> MyLineSegment;
};
