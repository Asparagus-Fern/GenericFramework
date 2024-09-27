#include "Base/PropertyEditCondition.h"

void FPropertyEditableState::Hide(const FString& DevReason)
{
#if !UE_BUILD_SHIPPING
	ensureAlwaysMsgf(!DevReason.IsEmpty(), TEXT("To Hide a Property, You Must Provide a Developer Reason."));
#endif

	bVisible = false;

#if !UE_BUILD_SHIPPING
	HiddenReasons.Add(DevReason);
#endif
}

void FPropertyEditableState::Disable(const FText& Reason)
{
	bEnabled = false;
	DisabledReasons.Add(Reason);
}

void FPropertyEditableState::DisableOption(const FString& Option)
{
#if !UE_BUILD_SHIPPING
	ensureAlwaysMsgf(!DisabledOptions.Contains(Option), TEXT("You've Already Disabled This Option."));
#endif

	DisabledOptions.Add(Option);
}

void FPropertyEditableState::UnableToReset()
{
	bResetable = false;
}

void FPropertyEditableState::Kill(const FString& DevReason)
{
	Hide(DevReason);
	UnableToReset();
}
