// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonEvent.h"
#include "CBE_HandleActorVisibility.generated.h"

USTRUCT(BlueprintType)
struct FActorVisibilityHandle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ActorTag = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsHiddenInGame = false;
};

/**
 * 处理Actor的显隐
 */
UCLASS()
class SCREENWIDGETGENERATION_API UCBE_HandleActorVisibility : public UCommonButtonEvent
{
	GENERATED_BODY()

public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	/* 激活时需要处理的显隐状态 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FActorVisibilityHandle> ActiveVisibilityHandles;

	/* 不激活时需要处理的显隐状态 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FActorVisibilityHandle> InactiveVisibilityHandles;
};
