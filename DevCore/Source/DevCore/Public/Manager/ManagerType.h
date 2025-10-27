// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ManagerType.generated.h"

DEVCORE_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogManager, Log, All);

class FManagerInterface;

USTRUCT(BlueprintType)
struct FManagerHandle
{
	GENERATED_BODY()

public:
	FManagerHandle();
	FManagerHandle(UObject* InOwner, FManagerInterface* InManager);
	~FManagerHandle();

	bool operator==(const FManagerHandle& Other) const { return ManagerID == Other.ManagerID; }
	bool operator==(const FGuid Other) const { return ManagerID == Other; }
	bool operator!=(const FManagerHandle& Other) const { return !(*this == Other); }
	bool operator!=(const FGuid Other) const { return !(*this == Other); }

	DEVCORE_API bool CheckIsValid() const;
	DEVCORE_API UObject* GetManagerOwner() const;
	DEVCORE_API FGuid GetManagerID() const;
	DEVCORE_API FManagerInterface* GetManager() const;

private:
	UPROPERTY()
	TObjectPtr<UObject> ManagerOwner = nullptr;

	FGuid ManagerID = FGuid::NewGuid();
	FManagerInterface* Manager = nullptr;
};
