// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNode.h"
#include "NativeGameplayTags.h"
#include "ActiveNode_Load.generated.h"

UCLASS()
class APPLICATIONRUNTIME_API AActiveNode_Load : public AActiveNode
{
	GENERATED_BODY()

public:
	AActiveNode_Load();
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "ActiveNode"))
	FGameplayTag ChangeNodeTag;
};
