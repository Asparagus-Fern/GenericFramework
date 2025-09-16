// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericRotatorBox.generated.h"

class UTextBlock;
class UGenericButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnElementRotated, int32, SelectedIndex, const FText&, SelectedText);

/**
 * 
 */
UCLASS()
class DEVSLATECORE_API UGenericRotatorBox : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void OnButtonLeftClicked();

	UFUNCTION()
	void OnButtonRightClicked();

public:
	UFUNCTION(BlueprintCallable)
	void RotateLeft();

	UFUNCTION(BlueprintCallable)
	void RotateRight();

	UFUNCTION(BlueprintCallable)
	void AddTextLabel(const FText& InTextLabel);

	UFUNCTION(BlueprintCallable)
	void RemoveTextLabel(const FText& InTextLabel);

	UFUNCTION(BlueprintCallable)
	void SetSelectedIndex(int32 Index);

	UFUNCTION(BlueprintPure)
	bool GetPreviousValidIndex(int32& OutIndex) const;

	UFUNCTION(BlueprintPure)
	bool GetNextValidIndex(int32& OutIndex) const;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnSelectedIndexChanged(int32 Index);

public:
	UPROPERTY(BlueprintAssignable)
	FOnElementRotated OnElementRotated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllowWrap = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefaultSelectedIndex = INDEX_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> TextLabels;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButton> GenericButton_Left;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButton> GenericButton_Right;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> TextBlock;

	int32 SelectedIndex = INDEX_NONE;
};
