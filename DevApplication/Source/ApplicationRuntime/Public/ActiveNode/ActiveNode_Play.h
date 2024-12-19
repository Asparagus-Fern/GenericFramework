// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveNode.h"
#include "NativeGameplayTags.h"
#include "ActiveNode_Play.generated.h"

class ACameraPointBase;
class UCameraHandle;
class UGameMenuSetting;
class UUserWidgetBase;

UCLASS()
class APPLICATIONRUNTIME_API AActiveNode_Play : public AActiveNode
{
	GENERATED_BODY()

public:
	AActiveNode_Play();
	virtual void LoginNode_Implementation() override;
	virtual void LogoutNode_Implementation() override;

	/* UI */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	UGameMenuSetting* DefaultGameMenu = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TArray<TSubclassOf<UUserWidgetBase>> DefaultOpenWidgetClasses;

	/* Camera */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Camera"), Category="Camera")
	FGameplayTag DefaultCameraTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Camera")
	UCameraHandle* CameraHandle = nullptr;

protected:
	UPROPERTY(Transient)
	TArray<UUserWidgetBase*> DefaultOpenWidgets;

protected:
	virtual void PostHUDCreated();
	virtual void OnCameraPointRegister(ACameraPointBase* InCameraPoint);
};
