#pragma once

#include "LevelStreamingType.generated.h"

LEVELSTREAMING_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogLevelStreaming, Log, All);

DECLARE_DELEGATE(FOnHandleLevelStreamingOnceFinish);

DECLARE_DELEGATE(FOnHandleLevelStreamingFinish);

DECLARE_DELEGATE(FOnLevelVisibilityChanged);

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLoadLevelStreamingSetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> Level = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMakeVisibleAfterLoad = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldBlockOnLoad = false;

public:
	FLoadLevelStreamingSetting() { return; }

	FLoadLevelStreamingSetting(const TSoftObjectPtr<UWorld>& InLevel, const bool MakeVisibleAfterLoad, const bool ShouldBlockOnLoad)
		: Level(InLevel),
		  bMakeVisibleAfterLoad(MakeVisibleAfterLoad),
		  bShouldBlockOnLoad(ShouldBlockOnLoad) { return; }

	bool IsValid() const { return !Level.IsNull(); }

	bool operator==(const FLoadLevelStreamingSetting& Other) const { return Level == Other.Level; }
	bool operator==(const TSoftObjectPtr<UWorld>& Other) const { return Level == Other; }
	bool operator!=(const FLoadLevelStreamingSetting& Other) const { return !(*this == Other); }
	bool operator!=(const TSoftObjectPtr<UWorld>& Other) const { return !(*this == Other); }
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FUnloadLevelStreamingSetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> Level = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldBlockOnUnload = false;

public:
	FUnloadLevelStreamingSetting() { return; }

	FUnloadLevelStreamingSetting(const TSoftObjectPtr<UWorld>& InLevel, const bool ShouldBlockOnUnload)
		: Level(InLevel),
		  bShouldBlockOnUnload(ShouldBlockOnUnload) { return; }

	bool IsValid() const { return !Level.IsNull(); }

	bool operator==(const FUnloadLevelStreamingSetting& Other) const { return Level == Other.Level; }
	bool operator==(const TSoftObjectPtr<UWorld>& Other) const { return Level == Other; }
	bool operator!=(const FUnloadLevelStreamingSetting& Other) const { return !(*this == Other); }
	bool operator!=(const TSoftObjectPtr<UWorld>& Other) const { return !(*this == Other); }
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FSetLevelStreamingVisibilitySetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> Level = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bVisible = false;

public:
	FSetLevelStreamingVisibilitySetting() { return; }

	FSetLevelStreamingVisibilitySetting(const TSoftObjectPtr<UWorld>& InLevel, const bool Visible)
		: Level(InLevel),
		  bVisible(Visible) { return; }

	bool IsValid() const { return !Level.IsNull(); }

	bool operator==(const FSetLevelStreamingVisibilitySetting& Other) const { return Level == Other.Level; }
	bool operator==(const TSoftObjectPtr<UWorld>& Other) const { return Level == Other; }
	bool operator!=(const FSetLevelStreamingVisibilitySetting& Other) const { return !(*this == Other); }
	bool operator!=(const TSoftObjectPtr<UWorld>& Other) const { return !(*this == Other); }
};
