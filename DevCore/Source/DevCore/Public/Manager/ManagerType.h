// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ManagerType.generated.h"

class FCoreInternalManager;

USTRUCT(BlueprintType)
struct FManagerHandle
{
	GENERATED_BODY()

public:
	FManagerHandle();
	FManagerHandle(UObject* InOwner, const TSharedRef<FCoreInternalManager>& InManager);

	bool operator==(const FManagerHandle& Other) const { return ManagerID == Other.ManagerID; }
	bool operator==(const FGuid Other) const { return ManagerID == Other; }
	bool operator!=(const FManagerHandle& Other) const { return !(*this == Other); }
	bool operator!=(const FGuid Other) const { return !(*this == Other); }

	DEVCORE_API bool CheckIsValid() const;
	DEVCORE_API UObject* GetManagerOwner() const;
	DEVCORE_API FGuid GetManagerID() const;
	DEVCORE_API TSharedRef<FCoreInternalManager> GetManager() const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ManagerName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ManagerOrder = INDEX_NONE;

private:
	UPROPERTY()
	UObject* ManagerOwner = nullptr;

	FGuid ManagerID;
	TSharedPtr<FCoreInternalManager> Manager;
};
