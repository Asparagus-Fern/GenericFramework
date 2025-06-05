// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeAPIInterface.h"
#include "Components/ActorComponent.h"
#include "NativeAPIProxyComponent.generated.h"

USTRUCT()
struct FNativeAPISignature
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Default)
	FString EntityClass;

	UPROPERTY(EditAnywhere, Category = Default)
	FString Entity;

	UPROPERTY(VisibleInstanceOnly, Category = Default)
	FString EntityPath;
};

/**
 * Native API 代理组件.
 * 挂载此组件, 为 Actor 提供 NativeAPI 支持.
 */
UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))
class UNativeAPIProxyComponent final : public UActorComponent, public INativeAPIEntityInterface
{
	GENERATED_BODY()

public:
	UNativeAPIProxyComponent(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	virtual void PostInitProperties() override;
#endif
	
	static FName NativeAPIProxyComponentDefaultName;

protected:
	// Begin UActorComponent Interface.
	virtual void OnRegister() override;
	virtual void OnUnregister() override;

#if WITH_EDITOR
	virtual void OnComponentCreated() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
#endif
	// End UActorComponent Interface.

	// Begin NativeAPI Interface.
	virtual void ProcessingNativeAPI(const FNativeAPIPayload& Payload) const override;
	// End NativeAPI Interface.

	// Begin NativeAPIEntity Interface.
	virtual FString GetEntity() const override;
	virtual UClass* GetEntityClass() const override;
	// End NativeAPIEntity Interface.

public:
	UFUNCTION(BlueprintCallable, Category = NativeAPI)
	void SetProcessOnOwnerHiddenEnable(bool bEnable);
	
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = Default)
	FNativeAPISignature NativeAPIEntity;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true", MultiLine), Category = Default)
	FString API;
#endif
	
	/* Owner 被显示标记为 Hidden In Game 时, Native API 应该工作吗？ [default = true] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = Default)
	uint8 bProcessOnOwnerHidden : 1;
};