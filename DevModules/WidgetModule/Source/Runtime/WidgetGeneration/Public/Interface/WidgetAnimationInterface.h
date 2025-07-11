// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/WidgetAnimationEvents.h"
#include "UObject/Interface.h"
#include "WidgetAnimationInterface.generated.h"

class UGenericWidget;
class UWidgetAnimation;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetActiveAnimationPlayFinish, UGenericWidget*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetInactiveAnimationPlayFinish, UGenericWidget*);

UINTERFACE(BlueprintType)
class UWidgetAnimationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WIDGETGENERATION_API IWidgetAnimationInterface
{
	GENERATED_BODY()

public:
	virtual bool HasWidgetAnimation(bool InIsActive) const = 0;
	virtual bool IsPlayingWidgetAnimation(bool InIsActive) const = 0;
	virtual float GetWidgetAnimationDuration(bool InIsActive) = 0;

	virtual UWidgetAnimation* GetActiveAnimation() const = 0;
	virtual void SetActiveAnimation(UWidgetAnimation* InAnimation) = 0;
	virtual UWidgetAnimation* GetInactiveAnimation() const = 0;
	virtual void SetInactiveAnimation(UWidgetAnimation* InAnimation) = 0;

	virtual void PlayWidgetAnimation(bool InIsActive) = 0;
	virtual void PlayWidgetAnimationRollback(bool InIsActive) = 0;
	virtual void PauseWidgetAnimation(bool InIsActive) = 0;
	virtual void StopWidgetAnimation(bool InIsActive) = 0;

	virtual void OnWidgetActiveAnimationPlayFinish() = 0;
	virtual void OnWidgetInactiveAnimationPlayFinish() = 0;

	FOnWidgetActiveAnimationPlayFinish& GetOnWidgetActiveAnimationPlayFinish() { return OnWidgetActiveAnimationPlayFinishEvent; }
	FOnWidgetInactiveAnimationPlayFinish& GetOnWidgetInactiveAnimationPlayFinish() { return OnWidgetInactiveAnimationPlayFinishEvent; }

protected:
	FWidgetAnimationDynamicEvent WidgetActiveAnimationFinishBinding;
	FWidgetAnimationDynamicEvent WidgetInactiveAnimationFinishBinding;

	FOnWidgetActiveAnimationPlayFinish OnWidgetActiveAnimationPlayFinishEvent;
	FOnWidgetInactiveAnimationPlayFinish OnWidgetInactiveAnimationPlayFinishEvent;
};
