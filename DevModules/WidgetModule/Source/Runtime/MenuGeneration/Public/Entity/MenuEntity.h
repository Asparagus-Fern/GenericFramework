// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MenuType.h"
#include "Common/CommonObject.h"
#include "MenuEntity.generated.h"

class UMenuCollection;
class UMenuContainer;
class UMenuStyle;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuEntity : public UCommonObject
{
	GENERATED_BODY()

public:
	UMenuEntity(const FObjectInitializer& ObjectInitializer);
	virtual void Initialize() override;
	virtual void DeInitialize() override;

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

	/* 坍塌，不可视，且不占据布局 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCollapsed = false;

	/* 隐藏，不可视，但占据布局 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bCollapsed"))
	bool bHidden = false;

	/* 可视，但是否无效化，当为false时，所有的交互将无效化 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "!bCollapsed && !bHidden"))
	bool bIsEnable = true;

	/* 可视，是否可被选择，当为false时，OnSelected/OnDeselected不再有效 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSelectable = true;

	/* 是否在选中时再次点击取消选中 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bSelectable"))
	bool bToggleable = false;

	/* 是否默认选中 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bSelectable"))
	bool bDefaultSelected = false;

	UPROPERTY()
	bool bUseStyleClass = true;

	/* 菜单样式类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bUseStyleClass"))
	TSubclassOf<UMenuStyle> StyleClass = nullptr;

	/* 菜单样式 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta=(EditConditionHides, EditCondition = "!bUseStyleClass"))
	UMenuStyle* Style = nullptr;

public:
	bool IsRootMenu() const { return bIsRoot; }

protected:
	uint8 bIsRoot : 1;
	uint8 bIsGroup : 1;
	TWeakPtr<UMenuCollection> Collection;
};
