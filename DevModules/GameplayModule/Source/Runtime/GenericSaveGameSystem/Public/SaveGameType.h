// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameType.generated.h"

class UGenericSaveGame;


/**
 * 
 */
USTRUCT(BlueprintType)
struct FSaveGameParameter
{
	GENERATED_BODY()

public:
	FSaveGameParameter();
	bool CanSave() const;
	bool CanLoad() const;
	bool CheckIsValid() const;
	bool operator==(const FSaveGameParameter& Other) const { return !GetSaveGameSlotName().IsEmpty() && !Other.GetSaveGameSlotName().IsEmpty() && GetSaveGameSlotName() == Other.GetSaveGameSlotName(); }
	bool operator==(const FString& Other) const { return !GetSaveGameSlotName().IsEmpty() && !Other.IsEmpty() && GetSaveGameSlotName() == Other; }
	bool operator!=(const FSaveGameParameter& Other) const { return !(*this == Other); }
	bool operator!=(const FString& Other) const { return !(*this == Other); }

public:
	FString GetSaveGameSlotName() const;

	FSimpleMulticastDelegate& GetOnSuccess() { return OnSuccessEvent; }
	FSimpleMulticastDelegate& GetOnFail() { return OnFailEvent; }

	void OnSuccess();
	void OnFail();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UGenericSaveGame* SaveGame = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString SaveName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 UserIndex = 0;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsAutoSave = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(UIMin = 0, ClampMin = 0, Units = "s", EditCondition = "bIsAutoSave"))
	float AutoSaveInterval = 120.f;

protected:
	FSimpleMulticastDelegate OnSuccessEvent;
	FSimpleMulticastDelegate OnFailEvent;
};
