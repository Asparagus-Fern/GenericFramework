// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InteractableWidgetEntity.h"
#include "MenuEntityBase.generated.h"

class UMenuCollection;
/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuEntityBase : public UInteractableWidgetEntity
{
	GENERATED_BODY()

public:
	UMenuEntityBase(const FObjectInitializer& ObjectInitializer);
	virtual void Initialize() override;
	virtual void DeInitialize() override;

	/* UMenuEntity */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.Menu"))
	FGameplayTag MenuTag = FGameplayTag::EmptyTag;

	/* 主要名字 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuMainName;

	/* 次要名字 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuSubName;

	/* 提示 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MenuToolTip;

	/* 图标 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MenuIcon = nullptr;

public:
	UFUNCTION(BlueprintPure)
	bool IsRootMenu() const { return bIsRoot; }

protected:
	uint8 bIsRoot : 1;
	TWeakPtr<UMenuCollection> Collection;

	// private:
	// 	FString GetEventName() const;
	// 	TArray<FString> SplitMenuTag() const;
};
