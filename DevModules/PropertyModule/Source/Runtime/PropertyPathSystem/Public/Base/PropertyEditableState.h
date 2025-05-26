#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"

class UPropertyEntity;

/**
 * 属性的可编辑状态
 */
class PROPERTYPATHSYSTEM_API FPropertyEditableState
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
