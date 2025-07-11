// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/GenericWidget.h"
#include "GenericHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericHUD : public UGenericWidget
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag HUDTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ViewportZOrder = 0;
};
