#pragma once

#include "LevelStreamingType.generated.h"

DECLARE_DELEGATE(FOnHandleLevelStreamingOnceFinish);

DECLARE_DELEGATE(FOnHandleLevelStreamingFinish);

DECLARE_DELEGATE(FOnVisibilityChangedFinish);

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLoadLevelStreamingSetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMakeVisibleAfterLoad = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldBlockOnLoad = false;

public:
	FLoadLevelStreamingSetting() { return; }

	FLoadLevelStreamingSetting(const TSoftObjectPtr<UWorld>& InLevel, const bool MakeVisibleAfterLoad, const bool ShouldBlockOnLoad)
		: Level(InLevel)
		  , bMakeVisibleAfterLoad(MakeVisibleAfterLoad)
		  , bShouldBlockOnLoad(ShouldBlockOnLoad) { return; }
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
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldBlockOnUnload = false;

public:
	FUnloadLevelStreamingSetting() { return; }

	FUnloadLevelStreamingSetting(const TSoftObjectPtr<UWorld>& InLevel, const bool ShouldBlockOnUnload)
		: Level(InLevel)
		  , bShouldBlockOnUnload(ShouldBlockOnUnload) { return; }
};


/**
 * 
 */
USTRUCT(BlueprintType)
struct FLevelStreamingVisibilitySetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULevelStreaming* LevelStreaming = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bVisible = false;

public:
	FLevelStreamingVisibilitySetting() { return; }

	FLevelStreamingVisibilitySetting(ULevelStreaming* InLevelStreaming, const bool Visible)
		: LevelStreaming(InLevelStreaming)
		  , bVisible(Visible) { return; }
};


/**
 * @brief 处理关卡流加载卸载与显示隐藏的基类
 */
UCLASS()
class ULevelStreamingHandleBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void HandleLoadLevel(const FLoadLevelStreamingSetting& LoadLevelStreamingSetting, FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish());
	virtual void HandleLoadLevels(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish InOnOnceFinishDelegate = FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish());
	virtual void HandleUnloadLevel(const FUnloadLevelStreamingSetting& UnloadLevelStreamingSetting, FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish());
	virtual void HandleUnloadLevels(TArray<FUnloadLevelStreamingSetting> InUnloadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish InOnOnceFinishDelegate = FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish());
	virtual void HandleSetLevelVisibility(FLevelStreamingVisibilitySetting InLevelStreamingVisibilitySetting, FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish());
	virtual void HandleSetLevelsVisibility(TArray<FLevelStreamingVisibilitySetting> InLevelStreamingVisibilitySettings, FOnHandleLevelStreamingOnceFinish InOnOnceFinishDelegate = FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish());

protected:
	int32 Index = 0;
	FOnHandleLevelStreamingOnceFinish OnOnceFinishDelegate;
	FOnHandleLevelStreamingFinish OnFinishDelegate;

	virtual void Load(const TSoftObjectPtr<UWorld>& Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FString& CallbackName, UObject* CallbackObject) const;
	virtual void Unload(const TSoftObjectPtr<UWorld>& Level, bool bShouldBlockOnUnload, const FString& CallbackName, UObject* CallbackObject) const;
	virtual void SetLevelVisibility(ULevelStreaming* LevelStreaming, bool bVisible);

protected:
	UFUNCTION()
	virtual void OnOnceFinish() { OnOnceFinishDelegate.ExecuteIfBound(); }

	UFUNCTION()
	virtual void OnFinish() { OnFinishDelegate.ExecuteIfBound(); }
};


/**
 * @brief 处理加载关卡流 
 */
UCLASS()
class ULoadLevelStreamingHandle : public ULevelStreamingHandleBase
{
	GENERATED_BODY()

public:
	virtual void HandleLoadLevel(const FLoadLevelStreamingSetting& LoadLevelStreamingSetting, FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish()) override;
	virtual void HandleLoadLevels(TArray<FLoadLevelStreamingSetting> InLoadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish InOnOnceFinishDelegate = FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish()) override;

protected:
	TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings;

	virtual void OnOnceFinish() override;
};


/**
 * @brief 处理卸载关卡流 
 */
UCLASS()
class UUnloadLevelStreamingHandle : public ULevelStreamingHandleBase
{
	GENERATED_BODY()

public:
	virtual void HandleUnloadLevel(const FUnloadLevelStreamingSetting& UnloadLevelStreamingSetting, FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish()) override;
	virtual void HandleUnloadLevels(TArray<FUnloadLevelStreamingSetting> InUnloadLevelStreamingSettings, FOnHandleLevelStreamingOnceFinish InOnOnceFinishDelegate = FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish InOnFinishDelegate = FOnHandleLevelStreamingFinish()) override;

protected:
	TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings;

	virtual void OnOnceFinish() override;
};


/**
 * @brief 处理关卡流显隐
 */
UCLASS()
class ULevelStreamingVisibilityHandle : public ULevelStreamingHandleBase
{
	GENERATED_BODY()

public:
	virtual void HandleSetLevelVisibility(FLevelStreamingVisibilitySetting InLevelStreamingVisibilitySetting, FOnHandleLevelStreamingFinish InOnFinishDelegate) override;
	virtual void HandleSetLevelsVisibility(TArray<FLevelStreamingVisibilitySetting> InLevelStreamingVisibilitySettings, FOnHandleLevelStreamingOnceFinish InOnOnceFinishDelegate, FOnHandleLevelStreamingFinish InOnFinishDelegate) override;

protected:
	TArray<FLevelStreamingVisibilitySetting> LevelStreamingVisibilitySettings;

	virtual void OnOnceFinish() override;
	virtual void OnFinish() override;
};

// struct FLevelsVisibilityHandle
// {
// public:
// 	FLevelsVisibilityHandle();
// 	FLevelsVisibilityHandle(TArray<TSoftObjectPtr<UWorld>> InLevels, bool InVisible, FOnOnceFinish InOnceFinish, FOnFinish InFinish);
//
// public:
// 	TArray<TSoftObjectPtr<UWorld>> Levels;
// 	bool bVisible;
// 	FOnOnceFinish OnOnceFinish;
// 	FOnFinish OnFinish;
// };
