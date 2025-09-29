// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ThreadType.generated.h"

class FGenericThread;

/**
 * 
 */
USTRUCT(BlueprintType)
struct GENERICTHREADSYSTEM_API FThreadHandle
{
	GENERATED_BODY()

public:
	FThreadHandle();
	FThreadHandle(FGuid InThreadGuid);

	bool operator==(const FThreadHandle& Other) const { return Other.ThreadGuid == ThreadGuid; }
	bool operator==(const FGuid Other) const { return Other == ThreadGuid; }
	bool operator!=(const FThreadHandle& Other) const { return !(*this == Other); }
	bool operator!=(const FGuid Other) const { return !(*this == Other); }

	FGuid GetThreadGuid() const { return ThreadGuid; }
	bool IsValid() const { return ThreadGuid.IsValid(); }

private:
	FGuid ThreadGuid;
};
