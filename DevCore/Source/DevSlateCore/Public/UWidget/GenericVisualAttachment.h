#pragma once

#include "Components/SizeBox.h"
#include "GenericVisualAttachment.generated.h"

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UGenericVisualAttachment : public USizeBox
{
	GENERATED_BODY()

public:
	UGenericVisualAttachment(const FObjectInitializer& ObjectInitializer);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetContentAnchor", BlueprintSetter="SetContentAnchor", Category="Visual Attachment")
	FVector2D ContentAnchor;

public:
	UFUNCTION(BlueprintPure, Category="Visual Attachment")
	FVector2D GetContentAnchor() const;

	UFUNCTION(BlueprintCallable, Category="Visual Attachment")
	void SetContentAnchor(FVector2D InAnchor);

private:
	TSharedPtr<class SVisualAttachmentBox> MyAttachmentBox;
};
