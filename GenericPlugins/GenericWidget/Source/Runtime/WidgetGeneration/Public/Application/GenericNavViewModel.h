// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "GenericNavViewModel.generated.h"

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UGenericNavViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SwitchLeft();

	UFUNCTION(BlueprintCallable)
	void SwitchRight();

public:
	UFUNCTION(FieldNotify, BlueprintPure)
	int32 GetNavNum() const;

	UFUNCTION(BlueprintCallable)
	void SetNavNum(int32 InNum);

	UFUNCTION(FieldNotify, BlueprintPure)
	int32 GetNavIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetNavIndex(int32 InIndex);

public:
	UPROPERTY(FieldNotify, EditAnywhere, BlueprintReadWrite)
	bool bAllowWrap = true;

	UPROPERTY(FieldNotify, EditAnywhere, meta=(ClampMin = 0, UIMin = 0), Getter, Setter, BlueprintGetter="GetNavNum", BlueprintSetter="SetNavNum")
	int32 NavNum = 0;

	UPROPERTY(FieldNotify, EditAnywhere, meta=(ClampMin = 0, UIMin = 0), Getter, Setter, BlueprintGetter="GetNavIndex", BlueprintSetter="SetNavIndex")
	int32 NavIndex = 0;
};
