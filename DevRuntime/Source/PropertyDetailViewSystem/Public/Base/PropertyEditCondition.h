#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"

class UPropertyEntity;

/**
 * 
 */
class PROPERTYDETAILVIEWSYSTEM_API FPropertyEditableState
{
public:
	FPropertyEditableState()
		: bVisible(true),
		  bEnabled(true),
		  bResetable(true)
	{
	}

	bool IsVisible() const { return bVisible; }
	bool IsEnabled() const { return bEnabled; }
	bool IsResetable() const { return bResetable; }

	const TArray<FText>& GetDisabledReasons() const { return DisabledReasons; }
	const TArray<FString>& GetDisabledOptions() const { return DisabledOptions; }

#if !UE_BUILD_SHIPPING
	const TArray<FString>& GetHiddenReasons() const { return HiddenReasons; }
#endif
	
	void Hide(const FString& DevReason);

	void Disable(const FText& Reason);

	void DisableOption(const FString& Option);

	template <typename EnumType>
	void DisableEnumOption(EnumType InEnumValue)
	{
		DisableOption(StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue));
	}

	void UnableToReset();

	void Kill(const FString& DevReason);

private:
	uint8 bVisible : 1;
	uint8 bEnabled : 1;
	uint8 bResetable : 1;

	TArray<FString> DisabledOptions;
	TArray<FText> DisabledReasons;

#if !UE_BUILD_SHIPPING
	TArray<FString> HiddenReasons;
#endif
};

/**
 * 
 */
class PROPERTYDETAILVIEWSYSTEM_API FPropertyEditCondition : public TSharedFromThis<FPropertyEditCondition>
{
public:
	FPropertyEditCondition() { return; }
	virtual ~FPropertyEditCondition() { return; }

	DECLARE_EVENT_OneParam(FPropertyEditCondition, FOnEditConditionChanged, bool);
	FOnEditConditionChanged OnEditConditionChangedEvent;

	void BroadcastEditConditionChanged() const { OnEditConditionChangedEvent.Broadcast(true); }

	virtual void Initialize(const UObject* InContext) { return; }

	virtual void Applied(const UObject* InContext, UPropertyEntity* Setting) const { return; }

	virtual void Changed(const UObject* InContext, UPropertyEntity* Setting, EPropertyChangeReason Reason) const { return; }

	virtual void GatherEditState(const UObject* InContext, FPropertyEditableState& InOutEditState) const { return; }

	virtual FString ToString() const { return TEXT(""); }
};
