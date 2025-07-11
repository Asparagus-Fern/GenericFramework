// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "BackpackItemData.generated.h"

/**
 * 
 */
UCLASS()
class BACKPACKSYSTEM_API UBackpackItemData : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, category="Backpack")
	int32 GetItemID() const;

	UFUNCTION(BlueprintCallable, category="Backpack")
	void SetItemID(int32 InItemID);

	UFUNCTION(BlueprintPure, category="Backpack")
	FName GetDisplayName() const;

	UFUNCTION(BlueprintCallable, category="Backpack")
	void SetDisplayName(FName InDisplayName);

	UFUNCTION(BlueprintPure, category="Backpack")
	FText GetTooltipText() const;

	UFUNCTION(BlueprintCallable, category="Backpack")
	void SetTooltipText(FText InTooltipText);

	UFUNCTION(BlueprintPure, category="Backpack")
	UTexture2D* GetIcon() const;

	UFUNCTION(BlueprintCallable, category="Backpack")
	void SetIcon(UTexture2D* InIcon);

	UFUNCTION(BlueprintPure, category="Backpack")
	int32 GetCount() const;

	UFUNCTION(BlueprintCallable, category="Backpack")
	void SetCount(int32 InCount);

	UFUNCTION(BlueprintPure, category="Backpack")
	TArray<FName> GetTags() const;

	UFUNCTION(BlueprintCallable, category="Backpack")
	void SetTags(TArray<FName> InTags);

public:
	UPROPERTY(VisibleAnywhere, FieldNotify, Getter, Setter, BlueprintGetter="GetItemID", BlueprintSetter="SetItemID", category="Backpack")
	int32 ItemID = 0;

	UPROPERTY(VisibleAnywhere, FieldNotify, Getter, Setter, BlueprintGetter="GetDisplayName", BlueprintSetter="SetDisplayName", category="Backpack")
	FName DisplayName = "Item Name";

	UPROPERTY(VisibleAnywhere, FieldNotify, Getter, Setter, BlueprintGetter="GetTooltipText", BlueprintSetter="SetTooltipText", category="Backpack")
	FText TooltipText = FText::FromString(TEXT("Item Tooltip"));

	UPROPERTY(VisibleAnywhere, FieldNotify, Getter, Setter, BlueprintGetter="GetIcon", BlueprintSetter="SetIcon", category="Backpack")
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(VisibleAnywhere, FieldNotify, Getter, Setter, BlueprintGetter="GetCount", BlueprintSetter="SetCount", category="Backpack")
	int32 Count = 0;

	UPROPERTY(VisibleAnywhere, FieldNotify, Getter, Setter, BlueprintGetter="GetTags", BlueprintSetter="SetTags", category="Backpack")
	TArray<FName> Tags;
};
