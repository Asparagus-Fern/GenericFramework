// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "ProcedureFlowActor.h"

#include "ProcedureFlow_Load.generated.h"

class ULoadingPanel;

UCLASS(Abstract, MinimalAPI)
class AProcedureFlow_Load : public AProcedureFlowActor
{
	GENERATED_BODY()

public:
	AProcedureFlow_Load();

protected:
	virtual void OnProcedureFlowEnter_Implementation() override;
	virtual void OnProcedureFlowExit_Implementation() override;

public:
	/* Enter Next Procedure Flow */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Procedure.Flow"))
	FGameplayTag NextProcedureFlowTag = FGameplayTag::EmptyTag;

	/* 加载界面UI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ULoadingPanel> LoadingClass = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void SwitchToNextProcedureFlow() const;

protected:
	UPROPERTY(Transient)
	ULoadingPanel* LoadingUI = nullptr;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void CreateLoadingPanel();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	int32 GetLoadingNum();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLoadingOnceFinish();
};
