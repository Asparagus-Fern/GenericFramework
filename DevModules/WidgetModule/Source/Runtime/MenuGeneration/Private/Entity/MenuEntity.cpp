// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuEntity.h"

#include "BPFunctions/BPFunctions_GameplayTag.h"

UMenuEntity::UMenuEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsRoot = false;
	bIsGroup = false;
}

void UMenuEntity::Initialize()
{
	Super::Initialize();

	const FGameplayTag RootMenuTag = FGameplayTag::RequestGameplayTag("UI.Menu");
	if (UBPFunctions_GameplayTag::GetDirectGameplayTagParent(MenuTag) == RootMenuTag)
	{
		bIsRoot = true;
	}
}

void UMenuEntity::DeInitialize()
{
	Super::DeInitialize();
}

FString UMenuEntity::GetEventName() const
{
	FString Result = "Event";
	for (auto& Split : SplitMenuTag())
	{
		Result += ("_" + Split);
	}
	return Result;
}

TArray<FString> UMenuEntity::SplitMenuTag() const
{
	TArray<FString> Results;

	TArray<FString> SplitWithPoint;
	FString SplitString = MenuTag.ToString();
	while (SplitString.Contains("."))
	{
		FString Split;
		SplitString.Split(".", &Split, &SplitString);
		SplitWithPoint.Add(Split);
	}

	for (auto& Split : SplitWithPoint)
	{
		if (Split.Contains("_"))
		{
			FString Result;
			Split.Split("_", nullptr, &Result);
			Results.Add(Result);
		}
	}

	return Results;
}
