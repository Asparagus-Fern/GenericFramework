// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/GameplayProcedure.h"
#include "LevelStreamingType.h"
#include "NativeGameplayTags.h"
#include "ProcedurePlay.generated.h"

class UUserWidgetBase;
class UGameMenuSetting;
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedurePlay_Default);

/**
 * 
 */
UCLASS()
class APPLICATIONRUNTIME_API UProcedurePlay : public UGameplayProcedure
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameMenuSetting* GameMenuSetting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UUserWidgetBase*> DefaultOpenWidgets;
};
