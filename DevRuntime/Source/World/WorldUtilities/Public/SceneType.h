#pragma once

#include "CoreMinimal.h"
#include "SceneType.generated.h"

/**
 * 蓝图可使用的WorldType
 */
UENUM(BlueprintType)
enum class ESceneWorldType : uint8
{
	/** An untyped world, in most cases this will be the vestigial worlds of streamed in sub-levels */
	None,
	/** The game world */
	Game,
	/** A world being edited in the editor */
	Editor,
	/** A Play In Editor world */
	PIE,
	/** A preview world for an editor tool */
	EditorPreview,
	/** A preview world for a game */
	GamePreview,
	/** A minimal RPC world for a game */
	GameRPC,
	/** An editor world that was loaded but not currently being edited in the level editor */
	Inactive
};

/* 蓝图WorldType转c++WorldType */
static EWorldType::Type ConvertSceneWorldTypeToWorldType(ESceneWorldType SceneWorldType)
{
	switch (SceneWorldType)
	{
	case ESceneWorldType::None:
		return EWorldType::None;

	case ESceneWorldType::Game:
		return EWorldType::Game;

	case ESceneWorldType::Editor:
		return EWorldType::Editor;

	case ESceneWorldType::PIE:
		return EWorldType::PIE;

	case ESceneWorldType::EditorPreview:
		return EWorldType::EditorPreview;

	case ESceneWorldType::GamePreview:
		return EWorldType::GamePreview;

	case ESceneWorldType::GameRPC:
		return EWorldType::GameRPC;

	case ESceneWorldType::Inactive:
		return EWorldType::Inactive;
	}

	return EWorldType::None;
}

/* c++WorldType转蓝图WorldType */
static ESceneWorldType ConvertWorldTypeToSceneWorldType(EWorldType::Type WorldType)
{
	switch (WorldType)
	{
	case EWorldType::None:
		return ESceneWorldType::None;

	case EWorldType::Game:
		return ESceneWorldType::Game;

	case EWorldType::Editor:
		return ESceneWorldType::Editor;

	case EWorldType::PIE:
		return ESceneWorldType::PIE;

	case EWorldType::EditorPreview:
		return ESceneWorldType::EditorPreview;

	case EWorldType::GamePreview:
		return ESceneWorldType::GamePreview;

	case EWorldType::GameRPC:
		return ESceneWorldType::GameRPC;

	case EWorldType::Inactive:
		return ESceneWorldType::Inactive;
	}

	return ESceneWorldType::None;
}

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
struct WORLDUTILITIES_API FFindActorHandle
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
struct WORLDUTILITIES_API FHandleActor
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
