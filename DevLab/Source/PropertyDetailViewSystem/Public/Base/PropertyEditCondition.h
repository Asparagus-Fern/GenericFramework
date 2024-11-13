#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"

class UPropertyEntity;

/**
 * 属性的可编辑状态
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

	/* 使属性隐藏 */
	void Hide(const FString& DevReason);

	/* 使属性失效 */
	void Disable(const FText& Reason);

	void DisableOption(const FString& Option);

	template <typename EnumType>
	void DisableEnumOption(EnumType InEnumValue)
	{
		DisableOption(StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue));
	}

	/* 当重置为默认值后，阻止重复重置 */
	void UnableToReset();

	/* 尽可能的使该属性消失 */
	void Kill(const FString& DevReason);

private:
	/* 是否可见 */
	uint8 bVisible : 1;

	/* 是否启用 */
	uint8 bEnabled : 1;

	/* 是否能重置回默认值，为false则表示当前已经是默认值 */
	uint8 bResetable : 1;

	TArray<FString> DisabledOptions;
	TArray<FText> DisabledReasons;

#if !UE_BUILD_SHIPPING
	TArray<FString> HiddenReasons;
#endif
};

/**
 * 属性的编辑条件，当属性的编辑条件未满足时将禁用该属性的UI
 */
class PROPERTYDETAILVIEWSYSTEM_API FPropertyEditCondition : public TSharedFromThis<FPropertyEditCondition>
{
public:
	FPropertyEditCondition() { return; }
	virtual ~FPropertyEditCondition() { return; }

public:
	DECLARE_EVENT_OneParam(FPropertyEditCondition, FOnEditConditionChanged, bool);

	FOnEditConditionChanged OnEditConditionChangedEvent;

	void BroadcastEditConditionChanged() const { OnEditConditionChangedEvent.Broadcast(true); }

public:
	/* 当属性Initialize时调用 */
	virtual void Initialize(const UObject* InContext) { return; }

	/* 当属性应用时 */
	virtual void Applied(const UObject* InContext, UPropertyEntity* Setting) const { return; }

	/* 当属性变更时 */
	virtual void Changed(const UObject* InContext, UPropertyEntity* Setting, EPropertyChangeReason Reason) const { return; }

	/* 当当前属性依赖的属性发生状态的变更时，重新评估当前属性的状态 */
	virtual void GatherEditState(const UObject* InContext, FPropertyEditableState& InOutEditState) const { return; }

	/* 调试文本 */
	virtual FString ToString() const { return TEXT(""); }
};
