#pragma once

#include "Components/SizeBox.h"
#include "VisualAttachment.generated.h"

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UVisualAttachment : public USizeBox
{
	GENERATED_BODY()

public:
	UVisualAttachment(const FObjectInitializer& ObjectInitializer);

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	UPROPERTY(EditAnywhere, Getter, Setter, BlueprintGetter="GetContentAnchor", BlueprintSetter="SetContentAnchor")
	FVector2D ContentAnchor;

public:
	UFUNCTION(BlueprintPure)
	FVector2D GetContentAnchor() const;

	UFUNCTION(BlueprintCallable)
	void SetContentAnchor(FVector2D InAnchor);

private:
	TSharedPtr<class SVisualAttachmentBox> MyAttachmentBox;
};
