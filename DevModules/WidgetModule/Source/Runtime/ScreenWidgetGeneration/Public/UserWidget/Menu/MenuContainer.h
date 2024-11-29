// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "MenuContainer.generated.h"

class UMenuStyle;
class UCommonButtonGroupBase;

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UMenuContainer : public UUserWidgetBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeOnCreate() override;

public:
	UPROPERTY(Transient, Getter, BlueprintGetter="GetCommonButtonGroup")
	UCommonButtonGroup* CommonButtonGroup = nullptr;

	UPROPERTY(Transient, Getter, BlueprintGetter="GetMenuStyles")
	TArray<UMenuStyle*> MenuStyles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsManagedByGroup = true;

public:
	UFUNCTION(BlueprintNativeEvent)
	void ConstructMenuContainer(UMenuStyle* MenuStyle, int32 Index);
	virtual void NativeConstructMenuContainer(UMenuStyle* MenuStyle, int32 Index);

	UFUNCTION(BlueprintNativeEvent)
	void DestructMenuContainer(UMenuStyle* MenuStyle);
	virtual void NativeDestructMenuContainer(UMenuStyle* MenuStyle);

	UFUNCTION(BlueprintNativeEvent)
	void PostConstructMenuContainer();
	virtual void NativePostConstructMenuContainer();

public:
	UFUNCTION(BlueprintPure)
	UCommonButtonGroup* GetCommonButtonGroup() const { return CommonButtonGroup; }

	UFUNCTION(BlueprintPure)
	TArray<UMenuStyle*> GetMenuStyles() const { return MenuStyles; }

#if WITH_EDITORONLY_DATA

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay)
	TSubclassOf<UMenuStyle> DesignMenuStyleClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay)
	int32 DesignMenuNum = 5;

protected:
	UPROPERTY(Transient)
	TArray<UMenuStyle*> DesignMenuStyles;

#endif
};
