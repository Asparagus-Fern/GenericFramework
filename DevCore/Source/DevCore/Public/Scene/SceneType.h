#pragma once

#include "SceneType.generated.h"

/**
 * 
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
