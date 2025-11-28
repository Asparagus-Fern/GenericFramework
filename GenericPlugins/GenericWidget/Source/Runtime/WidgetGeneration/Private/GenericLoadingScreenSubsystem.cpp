// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericLoadingScreenSubsystem.h"

#include "GameDelegates.h"
#include "MoviePlayer.h"

UGenericLoadingScreenSubsystem* UGenericLoadingScreenSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameInstance()->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

bool UGenericLoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && !IsRunningDedicatedServer();
}

void UGenericLoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGenericLoadingScreenSubsystem::PostLoadMapWithWorld);
	FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UGenericLoadingScreenSubsystem::OnWorldBeginTearDown);
	FCoreDelegates::OnExit.AddUObject(this, &UGenericLoadingScreenSubsystem::OnExit);

	PlayLoadingScreen();
}

void UGenericLoadingScreenSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
	FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
	FCoreDelegates::OnExit.RemoveAll(this);
}

void UGenericLoadingScreenSubsystem::PostLoadMapWithWorld(UWorld* InWorld)
{
	StopLoadingScreen();
}

void UGenericLoadingScreenSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
	PlayLoadingScreen();
}

void UGenericLoadingScreenSubsystem::OnExit()
{
	StopLoadingScreen();
}

void UGenericLoadingScreenSubsystem::PlayLoadingScreen()
{
	/* If Game Is Exiting, Do Not Open The Loading Screen */
	if (IsEngineExitRequested())
	{
		return;
	}

	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreen.bMoviesAreSkippable = true;
	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	if (IGameMoviePlayer* GameMoviePlayer = GetMoviePlayer())
	{
		GameMoviePlayer->SetupLoadingScreen(LoadingScreen);
		GameMoviePlayer->PlayMovie();
	}
}

void UGenericLoadingScreenSubsystem::StopLoadingScreen()
{
	if (IGameMoviePlayer* GameMoviePlayer = GetMoviePlayer())
	{
		GameMoviePlayer->StopMovie();
	}
}
