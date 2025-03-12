#pragma once

#include "Components/SizeBox.h"
#include "DVisualAttachment.generated.h"

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UDVisualAttachment : public USizeBox
{
	GENERATED_BODY()

public:
	UDVisualAttachment(const FObjectInitializer& ObjectInitializer);

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif
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
