// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "GenericRotatorBox.generated.h"

class UGenericButton;

/**
 * 
 */
UCLASS(Abstract)
class DEVSLATECORE_API UGenericRotatorBox : public UCommonRotator
{
	GENERATED_BODY()

public:
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
	void SetIsAllowWrap(bool InIsAllowWrap);

	UFUNCTION(BlueprintCallable)
	void AddTextLabel(const FText& InTextLabel, int32 Index = -1);

	UFUNCTION(BlueprintCallable)
	void RemoveTextLabel(FText InTextLabel);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnOptionAdded(const FText& TextLabel);

	UFUNCTION(BlueprintImplementableEvent)
	void OnOptionRemoved(const FText& TextLabel);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllowWrap = false;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButton> GenericButton_Left;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UGenericButton> GenericButton_Right;
};
