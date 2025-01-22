// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "GenericButton.generated.h"

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
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

public:
	/** If true, this button is enabled. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bButtonEnabled;

	/** If true, this button can be interacted with it normally. Otherwise, it will not react to being hovered or clicked. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bInteractionEnabled = true;

	/** The minimum width of the button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MinWidth;

	/** The minimum height of the button */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MinHeight;

public:
	/** Called when the button is clicked */
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnButtonDoubleClickedDelegate OnDoubleClicked;

	/** Called when the button receives focus */
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnButtonReceivedFocusDelegate OnReceivedFocus;

	/** Called when the button loses focus */
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnButtonLostFocusDelegate OnLostFocus;

public:
	UFUNCTION(BlueprintCallable)
	void SetButtonEnabled(bool bInIsButtonEnabled);

	UFUNCTION(BlueprintCallable)
	void SetInteractionEnabled(bool bInIsInteractionEnabled);

	UFUNCTION(BlueprintCallable)
	void SetButtonFocusable(bool bInIsButtonFocusable);

	UFUNCTION(BlueprintCallable)
	void SetMinDesiredHeight(int32 InMinHeight);

	UFUNCTION(BlueprintCallable)
	void SetMinDesiredWidth(int32 InMinWidth);

	virtual bool IsHovered() const override;
	bool IsPressed() const;

protected:
	virtual FReply SlateHandleClickedOverride();
	virtual void SlateHandlePressedOverride();
	virtual void SlateHandleReleasedOverride();
	virtual FReply SlateHandleDoubleClicked();
	virtual void SlateHandleOnReceivedFocus();
	virtual void SlateHandleOnLostFocus();

protected:
	/** Cached pointer to the underlying slate button owned by this UWidget */
	TSharedPtr<SBox> MyBox;

	/** Cached pointer to the underlying slate button owned by this UWidget */
	TSharedPtr<SGenericButton> MyGenericButton;
};
