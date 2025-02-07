// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InteractableWidgetEntity.h"
#include "MenuEntityBase.generated.h"

class UMenuCollection;

USTRUCT(BlueprintType)
struct FMenuEntityEvent
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuEntityBase : public UInteractableWidgetEntity
{
	GENERATED_BODY()

	friend UMenuCollection;

public:
	UMenuEntityBase(const FObjectInitializer& ObjectInitializer);
	virtual void Initialize() override;
	virtual void DeInitialize() override;

	/* UInteractableWidgetEntity */
protected:
	virtual void OnEntitySelectionChanged_Implementation(bool Selection) override;

	/* IWidgetEntityInterface */
public:
	virtual void OpenEntityWidget_Implementation() override;
	virtual void CloseEntityWidget_Implementation() override;

	/* IStateInterface */
public:
	virtual void OnCreate_Implementation() override;
	virtual void OnActived_Implementation() override;
	virtual void OnInactived_Implementation() override;
	virtual void OnDestroy_Implementation() override;
	
	/* UMenuEntity */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient)
	FMenuEntityEvent MenuEntityEvent;

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

public:
	virtual FName GetSelectedEventName();

protected:
	uint8 bIsRoot : 1;

	UPROPERTY()
	TWeakObjectPtr<UMenuCollection> Collection;

	FString GetEventBaseName() const;
	TArray<FString> GetSplitMenuTagNames() const;
};
