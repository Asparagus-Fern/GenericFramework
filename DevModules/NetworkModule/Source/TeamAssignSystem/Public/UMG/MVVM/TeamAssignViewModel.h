// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TeamAssignViewModel.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UTeamAssignViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	bool GetIsEnableMidwayPlayerLogin() const;

	UFUNCTION(BlueprintCallable)
	void SetIsEnableMidwayPlayerLogin(bool IsEnable);

	UFUNCTION(BlueprintPure)
	bool GetIsAutoFinishAssignTeam() const;

	UFUNCTION(BlueprintCallable)
	void SetIsAutoFinishAssignTeam(bool IsAutoFinish);

	UFUNCTION(BlueprintPure)
	int32 GetTeamCount() const;

	UFUNCTION(BlueprintCallable)
	void SetTeamCount(int32 InTeamCount);

protected:
	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetIsEnableMidwayPlayerLogin", BlueprintSetter="SetIsEnableMidwayPlayerLogin")
	bool IsEnableMidwayPlayerLogin = true;

	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetIsAutoFinishAssignTeam", BlueprintSetter="SetIsAutoFinishAssignTeam")
	bool IsAutoFinishAssignTeam = true;

	UPROPERTY(FieldNotify, EditDefaultsOnly, Getter, Setter, BlueprintGetter="GetTeamCount", BlueprintSetter="SetTeamCount", meta=(UIMin = 1, ClampMin = 1))
	int32 TeamCount = 2;
};
