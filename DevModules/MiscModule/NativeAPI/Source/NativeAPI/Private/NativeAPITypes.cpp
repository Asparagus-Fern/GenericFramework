// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPITypes.h"
#include "NativeAPIInterface.h"

bool FNativeAPIPayload::IsConsumer(TScriptInterface<INativeAPIEntityInterface> InScript) const
{
	if (InScript == nullptr)
	{
		return false;
	}

	if (InScript->GetEntityClass()->GetClassPathName() != GetClassPath().GetAssetPath())
	{
		return false;
	}

	if (GetEntity() != InScript->GetEntity())
	{
		return false;
	}

	return true;
}

#if WITH_EDITOR
void FNativeAPIPayload::FixupFromPIE(int32 PIEInstance)
{
	if (EntityObjectPath.IsValid())
	{
		EntityObjectPath.FixupForPIE(PIEInstance);
	}

	if (WorldPath.IsValid())
	{
		WorldPath.FixupForPIE(PIEInstance);
	}
}
#endif
