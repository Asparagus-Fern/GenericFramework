// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "ProcedureFlowActor.h"

#include "ProcedureFlow_Load.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_Load);

UCLASS()
class APPLICATIONRUNTIME_API AProcedureFlow_Load : public AProcedureFlowActor
{
	GENERATED_BODY()

public:
	AProcedureFlow_Load();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	/* Enter Next Procedure Flow */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Procedure.Flow"))
	FGameplayTag NextProcedureFlowTag = FGameplayTag::EmptyTag;
};
