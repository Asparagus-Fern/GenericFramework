// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Widgets/Layout/SBox.h"
#include "GenericButton.generated.h"

class UGenericButtonStyle;
class SGenericButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonDoubleClickedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReceivedFocusDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonLostFocusDelegate);

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UGenericButton : public UButton
{
	GENERATED_BODY()

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("GenericFramework", "WidgetPaletteCategory", "Generic"); }
#endif
	
public:
	/* If true, this button is enabled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic Button")
	bool bButtonEnabled = true;

	/* If true, this button can be interacted with it normally. Otherwise, it will not react to being hovered or clicked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic Button")
	bool bInteractionEnabled = true;

	/* The minimum width of the button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic Button")
	int32 MinWidth;

	/* The minimum height of the button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Generic Button")
	int32 MinHeight;

public:
	/* Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnButtonDoubleClickedDelegate OnDoubleClicked;

	/* Called when the button receives focus */
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnButtonReceivedFocusDelegate OnReceivedFocus;

	/* Called when the button loses focus */
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnButtonLostFocusDelegate OnLostFocus;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Button")
	void SetButtonEnabled(bool bInIsButtonEnabled);

	UFUNCTION(BlueprintCallable, Category="Generic Button")
	void SetInteractionEnabled(bool bInIsInteractionEnabled);

	UFUNCTION(BlueprintCallable, Category="Generic Button")
	void SetButtonFocusable(bool bInIsButtonFocusable);

	UFUNCTION(BlueprintCallable, Category="Generic Button")
	void SetMinDesiredHeight(int32 InMinHeight);

	UFUNCTION(BlueprintCallable, Category="Generic Button")
	void SetMinDesiredWidth(int32 InMinWidth);

	bool IsButtonHovered() const;
	bool IsButtonPressed() const;

protected:
	virtual FReply SlateHandleClickedOverride();
	virtual void SlateHandlePressedOverride();
	virtual void SlateHandleReleasedOverride();
	virtual FReply SlateHandleDoubleClicked();
	virtual void SlateHandleOnReceivedFocus();
	virtual void SlateHandleOnLostFocus();

protected:
	/* Cached pointer to the underlying slate button owned by this UWidget */
	TSharedPtr<SBox> MyBox;

	/* Cached pointer to the underlying slate button owned by this UWidget */
	TSharedPtr<SGenericButton> MyGenericButton;
};
