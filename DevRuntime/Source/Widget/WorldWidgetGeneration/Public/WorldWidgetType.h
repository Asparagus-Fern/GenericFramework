#pragma once

#include "NativeGameplayTags.h"
#include "WorldWidgetPoint.h"

class AWorldWidgetPoint;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Point);

struct WORLDWIDGETGENERATION_API FWorldWidgetDelegates
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FWorldWidgetPointDelegate, AWorldWidgetPoint*)
	static FWorldWidgetPointDelegate OnWorldWidgetPointConstruction;
	static FWorldWidgetPointDelegate OnWorldWidgetPointDestroy;
};
