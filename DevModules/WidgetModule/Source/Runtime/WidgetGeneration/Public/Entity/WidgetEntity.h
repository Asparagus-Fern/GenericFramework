// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetEntityInterface.h"
#include "Base/UserWidgetBase.h"
#include "Generic/GenericObject.h"
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
	TObjectPtr<UUserWidgetBase> WidgetRef = nullptr;

public:
	bool HasValidWidget() const;
	UUserWidgetBase* GetWidget() const;
};

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class WIDGETGENERATION_API UWidgetEntity : public UGenericObject, public IStateInterface, public IWidgetEntityInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
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
	UUserWidgetBase* GetWidgetByClass(const TSubclassOf<UUserWidgetBase>& InClass);

	UFUNCTION(BlueprintPure)
	UUserWidgetBase* GetWidget();

	UFUNCTION(BlueprintCallable)
	void SetWidget(UUserWidgetBase* InWidget);

public:
	template <typename T>
	T* GetWidget()
	{
		if (WidgetInternal.IsValid())
		{
			return Cast<T>(WidgetInternal.Get());
		}
		return Cast<T>(DisplayWidget.GetWidget());
	}

protected:
	UPROPERTY()
	TWeakObjectPtr<UUserWidgetBase> WidgetInternal;
};
