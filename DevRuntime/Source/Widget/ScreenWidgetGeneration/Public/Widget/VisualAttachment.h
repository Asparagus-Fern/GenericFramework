// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonVisualAttachment.h"
#include "VisualAttachment.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = UI)
class SCREENWIDGETGENERATION_API UVisualAttachment : public USizeBox
{
	GENERATED_UCLASS_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter= "SetContentAnchor")
	FVector2D ContentAnchor;

public:
	UFUNCTION(BlueprintCallable)
	void SetContentAnchor(FVector2D InContentAnchor);

protected:
	TSharedPtr<class SVisualAttachmentBox> MyAttachmentBox;
};
