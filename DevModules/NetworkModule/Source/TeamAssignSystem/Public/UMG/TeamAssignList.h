// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/GenericWidget.h"
#include "TeamAssignList.generated.h"

class UTextBlock;
class UTeamInformation;

/**
 * 
 */
UCLASS(Abstract)
class TEAMASSIGNSYSTEM_API UTeamAssignList : public UGenericWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTeamInformation> TeamInformation = nullptr;
};
