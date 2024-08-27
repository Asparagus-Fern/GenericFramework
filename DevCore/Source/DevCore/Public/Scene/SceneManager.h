// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreManager.h"
#include "SceneManager.generated.h"

/**
 * 查找Actor的方式
 */
UENUM(BlueprintType)
enum class EFindActorMethod : uint8
{
	Class,
	Tag,
	ClassAndTag,
	Interface
};

/**
 * 用于查找Actor的句柄
 */
USTRUCT(BlueprintType)
struct DEVCORE_API FFindActorHandle
{
	GENERATED_BODY()

public:
	FFindActorHandle();
	bool operator==(const FFindActorHandle OtherHandle) const { return ID == OtherHandle.ID; }
	bool operator==(const FGuid OtherID) const { return ID == OtherID; }
	bool GetIsValid() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFindActorMethod FindActorMethod = EFindActorMethod::Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "FindActorMethod == EFindActorMethod::Tag || FindActorMethod == EFindActorMethod::ClassAndTag"))
	FName ActorTag = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "FindActorMethod == EFindActorMethod::Class || FindActorMethod == EFindActorMethod::ClassAndTag"))
	TSubclassOf<AActor> ActorClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "FindActorMethod == EFindActorMethod::Interface"))
	TSubclassOf<UInterface> ActorInterface = nullptr;

public:
	FGuid ID;
};

/**
 * 已查找到Actor的句柄
 */
USTRUCT()
struct FFoundActorHandle
{
	GENERATED_BODY()

public:
	bool operator==(const FFoundActorHandle OtherHandle) const { return FindActorHandle == OtherHandle.FindActorHandle; }
	bool operator==(const FFindActorHandle& OtherHandle) const { return FindActorHandle == OtherHandle.ID; }
	bool operator==(const FGuid OtherID) const { return FindActorHandle == OtherID; }

public:
	UPROPERTY()
	FFindActorHandle FindActorHandle;

	UPROPERTY()
	TArray<AActor*> FoundActors;
};

/**
 * 
 */
UENUM(BlueprintType)
enum class EHandleActorMethod : uint8
{
	None,
	HandleActorLocation,
	HandleActorRotation,
	HandleActorScale,
	HandleActorHiddenInGame
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEVCORE_API FHandleActor
{
	GENERATED_BODY()

public:
	bool GetIsValid() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<EHandleActorMethod> HandleActorMethods;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector NewActorLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator NewActorRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector NewActorScale = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool NewActorHiddenInGame = false;
};

/**
 * 
 */
UCLASS()
class DEVCORE_API USceneManager : public UCoreManager
{
	GENERATED_BODY()

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

public:
	TArray<AActor*> FindActors(const FFindActorHandle& FindActorHandle, bool bUpdate = false);

protected:
	UPROPERTY(Transient)
	TArray<FFoundActorHandle> FoundActorHandles;
};
