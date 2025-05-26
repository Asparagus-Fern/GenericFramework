// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericSetting.h"
#include "CameraManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class CAMERASYSTEM_API UCameraManagerSetting : public UGenericSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

#if WITH_EDITOR
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("Camera")); }
#endif

public:
	UPROPERTY(Config, EditAnywhere)
	bool bDestroyEmptyCameraPointAfterSwitchFinish = true;
};
