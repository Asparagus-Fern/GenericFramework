#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"

class FPropertyEditableState;
class UPropertyEntity;

/**
 * 属性的编辑条件，当属性的编辑条件未满足时将禁用该属性的UI
 */
class PROPERTYPATHSYSTEM_API FPropertyEditCondition : public TSharedFromThis<FPropertyEditCondition>
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
	virtual void Applied(const UObject* InContext, UPropertyEntity* Property) const { return; }

	/* 当属性变更时 */
	virtual void Changed(const UObject* InContext, UPropertyEntity* Property, EPropertyChangeReason Reason) const { return; }

	/* 当当前属性依赖的属性发生状态的变更时，重新评估当前属性的状态 */
	virtual void GatherEditState(const UObject* InContext, FPropertyEditableState& InOutEditState) const { return; }

	/* 调试文本 */
	virtual FString ToString() const { return TEXT(""); }
};
