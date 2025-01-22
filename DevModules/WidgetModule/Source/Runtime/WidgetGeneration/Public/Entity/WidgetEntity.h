// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonObject.h"
#include "WidgetEntityInterface.h"
#include "Base/UserWidgetBase.h"
#include "WidgetEntity.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class WIDGETGENERATION_API UWidgetEntity : public UCommonObject, public IStateInterface, public IWidgetEntityInterface
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bUseClass = true;

	UPROPERTY(EditAnywhere, meta=(EditConditionHides, EditCondition = "bUseClass"))
	TSubclassOf<UUserWidgetBase> WidgetClass = nullptr;

	UPROPERTY(EditAnywhere, Instanced, meta=(EditConditionHides, EditCondition = "!bUseClass"))
	UUserWidgetBase* WidgetRef = nullptr;

	/* IStateInterface */
public:
	virtual void OnCreate_Implementation() override;
	virtual void OnDestroy_Implementation() override;

	/* IWidgetEntityInterface */
public:
	virtual void OpenEntityWidget_Implementation() override;
	virtual void CloseEntityWidget_Implementation() override;

	/* UWidgetEntity */
public:
	UFUNCTION(BlueprintPure)
	bool HasValidWidget() const;

	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "InClass"))
	UUserWidgetBase* GetWidgetByClass(TSubclassOf<UUserWidgetBase> InClass);

	UFUNCTION(BlueprintPure)
	UUserWidgetBase* GetWidget();

public:
	template <typename T>
	T* GetWidget()
	{
		if (IsValid(Widget))
		{
			return Cast<T>(Widget);
		}

		if (!HasValidWidget())
		{
			DLOG(DLogUI, Warning, TEXT("Entity Has No Widget"))
			return nullptr;
		}

		T* Result = nullptr;
		if (bUseClass)
		{
			Widget = CreateWidget<UUserWidgetBase>(GetWorld(), WidgetClass);
			Result = Cast<T>(Widget);
		}
		else
		{
			Widget = WidgetRef;
			Result = Cast<T>(Widget);
		}

		return Result;
	}

protected:
	UPROPERTY()
	TObjectPtr<UUserWidgetBase> Widget = nullptr;
};
