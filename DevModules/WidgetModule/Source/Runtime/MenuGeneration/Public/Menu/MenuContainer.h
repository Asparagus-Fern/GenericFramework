// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "MenuContainer.generated.h"

class UMenuGroupEntity;
class UMenuStyle;

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuContainer : public UUserWidgetBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void ConstructMenuContainer(UMenuStyle* MenuStyle, int32 Index);
	virtual void NativeConstructMenuContainer(UMenuStyle* MenuStyle, int32 Index);

	UFUNCTION(BlueprintNativeEvent)
	void PostConstructMenuContainer();
	virtual void NativePostConstructMenuContainer();

	UFUNCTION(BlueprintPure)
	UMenuGroupEntity* GetMenuGroupEntity();

protected:
	UPROPERTY(Transient, BlueprintReadOnly, Transient)
	TArray<UMenuStyle*> MenuStyles;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<class UPanelWidget> Content;

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
