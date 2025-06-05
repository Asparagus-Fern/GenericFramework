// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPIWorldSubsystem.h"
#include "NativeAPIProxyComponent.h"
#include "NativeAPITypes.h"
#include "NativeAPILog.h"
#include "Debug/DebugType.h"

UNativeAPIWorldSubsystem* UNativeAPIWorldSubsystem::Get(const UWorld* World)
{
	return UWorld::GetSubsystem<UNativeAPIWorldSubsystem>(World);
}

bool UNativeAPIWorldSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UNativeAPIWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UNativeAPIWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();

	NativeAPIProxyCollection.Empty();
}

bool UNativeAPIWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::PIE || WorldType == EWorldType::Game;
}

void UNativeAPIWorldSubsystem::ProcessingNativeAPI(const FNativeAPIPayload& Payload) const
{
	check(Payload.IsValid())

	if (NativeAPIProxyCollection.IsEmpty())
	{
		return;
	}

	const UWorld* World = GetWorld();

	if (!World->IsInitialized() || !World->HasBegunPlay())
	{
		return;
	}

	TArray<UClass*> Classes;
	NativeAPIProxyCollection.GenerateKeyArray(Classes);

	UClass** Class = Classes.FindByPredicate([Payload](const UClass* Other)
		{
			return Other->GetClassPathName() == Payload.GetClassPath().GetAssetPath();
		}
	);

	if (Class != nullptr)
	{
		auto Values = NativeAPIProxyCollection[*Class];

		for (auto It = Values.CreateIterator(); It; ++It)
		{
			const TScriptInterface<INativeAPIEntityInterface> Script(*It);
			Script->ProcessingNativeAPI(Payload);
		}
	}
	else
	{
		GenericLOG(LogNativeAPI, Display, TEXT("World NativeAPI 没有被处理, 当前没有这个类型的注册对象. %s"), *Payload.GetClassPath().ToString())
	}
}

void UNativeAPIWorldSubsystem::RegisterNativeAPI(UNativeAPIProxyComponent* InProxy)
{
	const TScriptInterface<INativeAPIEntityInterface> Script(InProxy);
	UClass* Class = Script->GetEntityClass();

	check(Class);

	auto& Values = NativeAPIProxyCollection.FindOrAdd(Class);
	if (!Values.Contains(InProxy))
	{
		Values.Add(InProxy);
	}
}

void UNativeAPIWorldSubsystem::UnRegisterNativeAPI(UNativeAPIProxyComponent* InProxy)
{
	const TScriptInterface<INativeAPIEntityInterface> Script(InProxy);

	const UClass* Class = Script->GetEntityClass();

	check(Class);

	if (NativeAPIProxyCollection.Contains(Class))
	{
		auto Values = NativeAPIProxyCollection[Class];
		if (Values.Contains(InProxy))
		{
			Values.RemoveSwap(InProxy);
		}

		if (Values.IsEmpty())
		{
			NativeAPIProxyCollection.Remove(Class);
		}
	}
}
