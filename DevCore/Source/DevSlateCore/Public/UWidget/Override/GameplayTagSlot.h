// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Components/NamedSlot.h"
#include "GameplayTagSlot.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_HUD);
class UGameplayTagSlot;

/**
 * 带GameplayTag的插槽
 */
UCLASS()
class DEVSLATECORE_API UGameplayTagSlot : public UNamedSlot
{
	GENERATED_BODY()

protected:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return NSLOCTEXT("DevWidget", "Common", "Dev Widget"); }
#endif
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;

public:
	/* 是否手动的注册插槽 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bManualRegistration = false;

	/* 插槽标签 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag SlotTag;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayTagSlotDelegate, UGameplayTagSlot*)
	static FGameplayTagSlotDelegate OnGameplayTagSlotBuild;
	static FGameplayTagSlotDelegate OnGameplayTagSlotDestroy;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotContentChanged, UWidget*, Widget);

	UPROPERTY(BlueprintAssignable)
	FOnSlotContentChanged OnSlotContentAdded;

	UPROPERTY(BlueprintAssignable)
	FOnSlotContentChanged OnSlotContentRemoved;
};
