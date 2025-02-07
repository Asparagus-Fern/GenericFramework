// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonObject.h"
#include "WidgetEntityInterface.h"
#include "WidgetManager.h"
#include "Base/UserWidgetBase.h"
#include "Manager/ManagerStatics.h"
#include "WidgetEntity.generated.h"

USTRUCT(BlueprintType)
struct WIDGETGENERATION_API FDisplayWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bUseClass = true;

	UPROPERTY(EditAnywhere, meta=(EditConditionHides, EditCondition = "bUseClass"))
	TSubclassOf<UUserWidgetBase> WidgetClass = nullptr;

	UPROPERTY(EditAnywhere, Instanced, meta=(EditConditionHides, EditCondition = "!bUseClass"))
	UUserWidgetBase* WidgetRef = nullptr;

public:
	bool HasValidWidget() const;
	UUserWidgetBase* GetWidget();

public:
	template <typename T>
	T* GetWidget()
	{
		if (IsValid(WidgetInternal))
		{
			return Cast<T>(WidgetInternal);
		}

		if (!HasValidWidget())
		{
			DLOG(DLogUI, Warning, TEXT("Entity Has No Widget"))
			return nullptr;
		}

		T* Result = nullptr;
		if (bUseClass)
		{
			WidgetInternal = CreateWidget<UUserWidgetBase>(GetManager<UWidgetManager>()->GetWorld(), WidgetClass);
			Result = Cast<T>(WidgetInternal);
		}
		else
		{
			WidgetInternal = WidgetRef;
			Result = Cast<T>(WidgetInternal);
		}

		return Result;
	}

protected:
	UPROPERTY()
	TObjectPtr<UUserWidgetBase> WidgetInternal = nullptr;
};

/**
 * 
 */
UCLASS(Abstract)
class WIDGETGENERATION_API UWidgetEntity : public UCommonObject, public IStateInterface, public IWidgetEntityInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FDisplayWidget DisplayWidget;

	/* IStateInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* IWidgetEntityInterface */
public:
	virtual void OpenEntityWidget_Implementation() override;
	virtual void CloseEntityWidget_Implementation() override;

protected:
	virtual void OnEntityWidgetInitialized();
	virtual void OnEntityWidgetDeinitialized();

	/* UWidgetEntity */
public:
	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "InClass"))
	UUserWidgetBase* GetWidgetByClass(TSubclassOf<UUserWidgetBase> InClass);

	UFUNCTION(BlueprintPure)
	UUserWidgetBase* GetWidget();
};
