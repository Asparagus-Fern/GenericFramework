// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuEntityBase.h"

#include "BPFunctions/BPFunctions_GameplayTag.h"
#include "Collection/MenuCollection.h"


UMenuEntityBase::UMenuEntityBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsRoot = false;
}

void UMenuEntityBase::Initialize()
{
	Super::Initialize();

	const FGameplayTag RootMenuTag = FGameplayTag::RequestGameplayTag("UI.Menu");
	if (UBPFunctions_GameplayTag::GetDirectGameplayTagParent(MenuTag) == RootMenuTag)
	{
		bIsRoot = true;
	}

	// if (UMenuCollection* OuterCollection = Cast<UMenuCollection>(GetOuter()))
	// {
	// 	const TSharedPtr<UMenuCollection> OuterCollectionPtr = MakeShareable(OuterCollection);
	// 	Collection = OuterCollectionPtr;
	// }
}

void UMenuEntityBase::DeInitialize()
{
	Super::DeInitialize();
}

/*FString UMenuEntityBase::GetEventName() const
{
	FString Result = "Event";
	for (auto& Split : SplitMenuTag())
	{
		Result += ("_" + Split);
	}
	return Result;
}

TArray<FString> UMenuEntityBase::SplitMenuTag() const
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
}*/
