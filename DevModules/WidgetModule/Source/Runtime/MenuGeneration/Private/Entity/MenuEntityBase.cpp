// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/MenuEntityBase.h"

#include "BPFunctions/BPFunctions_GameplayTag.h"
#include "Collection/MenuCollection.h"
#include "Menu/MenuStyle.h"

const FString SelectedEventName = "SelectedEvent";

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
}

void UMenuEntityBase::DeInitialize()
{
	Super::DeInitialize();
}

void UMenuEntityBase::OnEntitySelectionChanged_Implementation(bool Selection)
{
	Super::OnEntitySelectionChanged_Implementation(Selection);

	if (Selection)
	{
		NativeOnActived();
		// DPRINT(Log, TEXT("Selected : %s"), *MenuMainName.ToString())
	}
	else
	{
		NativeOnInactived();
		// DPRINT(Log, TEXT("Deselected : %s"), *MenuMainName.ToString())
	}

	/* Execute Event */
	if (Collection.IsValid())
	{
		FName EventName = GetSelectedEventName();
		UFunction* Function = Collection->FindFunction(GetSelectedEventName());

		if (UFunction* SelectedFunction = Collection->FindFunction(GetSelectedEventName()))
		{
			Collection->ProcessEvent(SelectedFunction, &Selection);
		}
	}
}

void UMenuEntityBase::OpenEntityWidget_Implementation()
{
	Super::OpenEntityWidget_Implementation();

	if (UMenuStyle* MenuStyle = Cast<UMenuStyle>(GetWidget()))
	{
		MenuStyle->NativeConstructMenuStyle();
	}
}

void UMenuEntityBase::CloseEntityWidget_Implementation()
{
	Super::CloseEntityWidget_Implementation();
}

void UMenuEntityBase::OnCreate_Implementation()
{
	Super::OnCreate_Implementation();
	IWidgetEntityInterface::Execute_OpenEntityWidget(this);
}

void UMenuEntityBase::OnActived_Implementation()
{
	Super::OnActived_Implementation();
}

void UMenuEntityBase::OnInactived_Implementation()
{
	Super::OnInactived_Implementation();
}

void UMenuEntityBase::OnDestroy_Implementation()
{
	Super::OnDestroy_Implementation();
	IWidgetEntityInterface::Execute_CloseEntityWidget(this);
}

FName UMenuEntityBase::GetSelectedEventName()
{
	return FName(SelectedEventName + "_" + GetEventBaseName());
}

FString UMenuEntityBase::GetEventBaseName() const
{
	FString Result;
	TArray<FString> SplitMenuTagNames = GetSplitMenuTagNames();
	for (int32 It = 0; It < SplitMenuTagNames.Num(); ++It)
	{
		if (It == 0)
		{
			Result = SplitMenuTagNames[It];
		}
		else
		{
			Result += ("_" + SplitMenuTagNames[It]);
		}
	}

	return Result;
}

TArray<FString> UMenuEntityBase::GetSplitMenuTagNames() const
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
	SplitWithPoint.Add(SplitString);

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
