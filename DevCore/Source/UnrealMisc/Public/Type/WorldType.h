// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "WorldType.generated.h"

/**
 * 蓝图可使用的WorldType
 */
UENUM(BlueprintType)
enum class EWorldTypeBP : uint8
{
	/* An untyped world, in most cases this will be the vestigial worlds of streamed in sub-levels */
	None,
	/* The game world */
	Game,
	/* A world being edited in the editor */
	Editor,
	/* A Play In Editor world */
	PIE,
	/* A preview world for an editor tool */
	EditorPreview,
	/* A preview world for a game */
	GamePreview,
	/* A minimal RPC world for a game */
	GameRPC,
	/* An editor world that was loaded but not currently being edited in the level editor */
	Inactive
};

/* 蓝图WorldType转c++WorldType */
static EWorldType::Type ConvertToWorldType(EWorldTypeBP SceneWorldType)
{
	switch (SceneWorldType)
	{
	case EWorldTypeBP::None:
		return EWorldType::None;

	case EWorldTypeBP::Game:
		return EWorldType::Game;

	case EWorldTypeBP::Editor:
		return EWorldType::Editor;

	case EWorldTypeBP::PIE:
		return EWorldType::PIE;

	case EWorldTypeBP::EditorPreview:
		return EWorldType::EditorPreview;

	case EWorldTypeBP::GamePreview:
		return EWorldType::GamePreview;

	case EWorldTypeBP::GameRPC:
		return EWorldType::GameRPC;

	case EWorldTypeBP::Inactive:
		return EWorldType::Inactive;
	}

	return EWorldType::None;
}

/* c++WorldType转蓝图WorldType */
static EWorldTypeBP ConvertWorldTypeBP(EWorldType::Type WorldType)
{
	switch (WorldType)
	{
	case EWorldType::None:
		return EWorldTypeBP::None;

	case EWorldType::Game:
		return EWorldTypeBP::Game;

	case EWorldType::Editor:
		return EWorldTypeBP::Editor;

	case EWorldType::PIE:
		return EWorldTypeBP::PIE;

	case EWorldType::EditorPreview:
		return EWorldTypeBP::EditorPreview;

	case EWorldType::GamePreview:
		return EWorldTypeBP::GamePreview;

	case EWorldType::GameRPC:
		return EWorldTypeBP::GameRPC;

	case EWorldType::Inactive:
		return EWorldTypeBP::Inactive;
	}

	return EWorldTypeBP::None;
}