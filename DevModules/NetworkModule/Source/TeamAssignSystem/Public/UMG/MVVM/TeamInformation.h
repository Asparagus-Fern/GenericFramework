// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TeamInformation.generated.h"

/**
 * 
 */
UCLASS()
class TEAMASSIGNSYSTEM_API UTeamInformation : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetTeamDisplayName() const;

	UFUNCTION(BlueprintCallable)
	void SetTeamDisplayName(FText InTeamDisplayName);

	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetMinTeamPlayerCount() const;

	UFUNCTION(BlueprintCallable)
	void SetMinTeamPlayerCount(int32 InMinTeamPlayerCount);

	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetMaxTeamPlayerCount() const;

	UFUNCTION(BlueprintCallable)
	void SetMaxTeamPlayerCount(int32 InMaxTeamPlayerCount);

private:
	UPROPERTY(FieldNotify, Getter, Setter, meta=(AllowPrivateAccess))
	FText TeamDisplayName = FText::FromString(TEXT("Team Display Name"));

	UPROPERTY(FieldNotify, Getter, Setter, meta=(UIMin = "1", ClampMin = "1", AllowPrivateAccess))
	int32 MinTeamPlayerCount = 1;

	UPROPERTY(FieldNotify, Getter, Setter, meta=(UIMin = "1", ClampMin = "1", AllowPrivateAccess))
	int32 MaxTeamPlayerCount = 4;
};
