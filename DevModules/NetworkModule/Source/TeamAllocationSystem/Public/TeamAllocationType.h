// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "TeamAllocationType.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_TeamAllocation);

USTRUCT(BlueprintType)
struct FTeamInformation : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Network.TeamAllocation"))
	FGameplayTag TeamID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DefaultTeamName;
};
