// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNode.h"
#include "NativeGameplayTags.h"
#include "ActiveNode_Play.generated.h"

class UUserWidgetBase;

UCLASS()
class APPLICATIONRUNTIME_API AActiveNode_Play : public AActiveNode
{
	GENERATED_BODY()

public:
	AActiveNode_Play();
	virtual void Login() override;
	virtual void Logout() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TArray<TSubclassOf<UUserWidgetBase>> DefaultOpenWidgetClasses;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TArray<UUserWidgetBase*> DefaultOpenWidgets;
};
