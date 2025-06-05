// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPISubsystem.h"

#include "INativeAPISessionFeature.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "NativeAPILog.h"
#include "NativeAPITypes.h"
#include "NativeAPIWorldSubsystem.h"
#include "Debug/DebugType.h"
#include "Features/IModularFeatures.h"

#if WITH_EDITOR
#include "Editor.h"
#else
#include "Misc/CoreDelegates.h"
#endif

bool UNativeAPISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UNativeAPISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

#if WITH_EDITOR
	FEditorDelegates::PostPIEStarted.AddUObject(this, &UNativeAPISubsystem::HandleOnPostPIEStarted);
	FEditorDelegates::EndPIE.AddUObject(this, &UNativeAPISubsystem::HandleOnEndPIE);
#else
	FWorldDelegates::OnStartGameInstance.AddUObject(this, &UNativeAPISubsystem::HandleOnStartGameInstance);
	FCoreDelegates::OnEnginePreExit.AddUObject(this, &UNativeAPISubsystem::HandleOnEnginePreExit);
#endif

	// IModularFeatures::Get().OnModularFeatureRegistered().AddUObject(this, &UNativeAPISubsystem::HandleOnNativeAPISessionFeatureRegistered);
}

void UNativeAPISubsystem::Deinitialize()
{
	Super::Deinitialize();

#if WITH_EDITOR
	FEditorDelegates::PostPIEStarted.RemoveAll(this);
	FEditorDelegates::EndPIE.RemoveAll(this);
#else
	FWorldDelegates::OnStartGameInstance.RemoveAll(this);
	FCoreDelegates::OnEnginePreExit.RemoveAll(this);
#endif
}

void UNativeAPISubsystem::SendSimulationNativeAPI(const FString& NativeAPIJson)
{
	this->SendSimulationNativeAPIMessage(NativeAPIJson);
}

void UNativeAPISubsystem::ProcessingNativeAPI(const FNativeAPIPayload& Payload) const
{
	check(Payload.IsValid());
	const UClass* EntityClass = Payload.GetClassPath().ResolveClass();

	if (!EntityClass)
	{
		GenericLOG(LogNativeAPI, Warning, TEXT("Type [%s] could not be found in memory."), *Payload.GetClassPath().ToString())
		return;
	}

	const FSoftObjectPath WorldPath = Payload.GetWorldPath();

	UWorld* TargetWorld = nullptr;
	if (WorldPath.IsValid())
	{
		TargetWorld = Cast<UWorld>(WorldPath.ResolveObject());
	}

	if (Payload.IsValidEntityPath())
	{
		if (TargetWorld == nullptr)
		{
			GenericLOG(LogNativeAPI, Error, TEXT("Native API cannot be directed to the world %s"), *Payload.GetWorldPath().ToString());
			return;
		}

		const FSoftObjectPath EntityPath = Payload.GetEntityPath();
		check(EntityPath.IsSubobject());

		UObject* FoundObject = nullptr;
		if (TargetWorld->ResolveSubobject(*EntityPath.GetSubPathString(), FoundObject, false))
		{
			if (!FoundObject->Implements<INativeAPIEntityInterface::UClassType>())
			{
				GenericLOG(LogNativeAPI, Error, TEXT("Native API Obect must implement by INativeAPIEntityInterface.  %s"), *EntityPath.ToString())
				return;
			}

			const TScriptInterface<INativeAPIEntityInterface> Script(FoundObject);
			check(Script != nullptr);
			check(Script->GetEntityClass() == EntityClass)
			Script->ProcessingNativeAPI(Payload);
		}
		else
		{
			GenericLOG(LogNativeAPI, Warning, TEXT("无法找到对象 : %s, 该对象不在内存当中或是执行路径有误"), *EntityPath.ToString())
		}
	}
	else
	{
		auto NativeAPIToWorld = [&Payload](const UWorld* World)
		{
			const UNativeAPIWorldSubsystem* NativeAPIWorldSubsystem = UNativeAPIWorldSubsystem::Get(World);

			if (NativeAPIWorldSubsystem != nullptr)
			{
				NativeAPIWorldSubsystem->ProcessingNativeAPI(Payload);
			}
			else
			{
				GenericLOG(LogNativeAPI, Error, TEXT("Native api can't broadcast to the world %s. invalid world subsystem !"), *World->GetName())
			}
		};

		if (TargetWorld != nullptr)
		{
			NativeAPIToWorld(TargetWorld);
		}
		else
		{
			// World Path并非必要字段, 如果没有一个明确的世界, 那么我们找到所有世界处理工作.
			const UEngine* Engine = CastChecked<UEngine>(GetOuter());

			for (auto WorldContext : Engine->GetWorldContexts())
			{
				if (WorldContext.WorldType == EWorldType::Game || WorldContext.WorldType == EWorldType::PIE)
				{
					NativeAPIToWorld(WorldContext.World());
				}
			}
		}
	}
}

#if WITH_EDITOR
void UNativeAPISubsystem::HandleOnPostPIEStarted(bool bIsSimulating) { StartAllFeatureSession(); }
void UNativeAPISubsystem::HandleOnEndPIE(bool bIsSimulating) { EndAllFeatureSession(); }
#else
void UNativeAPISubsystem::HandleOnStartGameInstance(UGameInstance* InGameInstance) { StartAllFeatureSession(); }
void UNativeAPISubsystem::HandleOnEnginePreExit() { EndAllFeatureSession(); }
#endif

/*void UNativeAPISubsystem::HandleOnNativeAPISessionFeatureRegistered(const FName& FeatureName, IModularFeature* Feature)
{
	if(FeatureName == INativeAPISessionFeature::GetFeatureName())
	{
		INativeAPISessionFeature* Session = static_cast<INativeAPISessionFeature*>(Feature);
		Session->SetReceiveSessionPayloadBinding(FOnReceiveNativePayload::CreateUObject(this, &UNativeAPISubsystem::HandleOnReceiveNativePayload));
		Session->StartSession();
	}
}*/

void UNativeAPISubsystem::StartAllFeatureSession()
{
	TArray<INativeAPISessionFeature*> NativeAPISessionFeatures = IModularFeatures::Get().GetModularFeatureImplementations<INativeAPISessionFeature>(INativeAPISessionFeature::GetFeatureName());
	for (const auto NativeAPISessionFeature : NativeAPISessionFeatures)
	{
		if (NativeAPISessionFeature->StartSession())
		{
			NativeAPISessionFeature->SetReceiveSessionPayloadBinding(FOnReceiveNativePayload::CreateUObject(this, &UNativeAPISubsystem::HandleOnReceiveNativePayload));
		}
	}
}

void UNativeAPISubsystem::EndAllFeatureSession()
{
	TArray<INativeAPISessionFeature*> NativeAPISessionFeatures = IModularFeatures::Get().GetModularFeatureImplementations<INativeAPISessionFeature>(INativeAPISessionFeature::GetFeatureName());

	for (const auto NativeAPISessionFeature : NativeAPISessionFeatures)
	{
		NativeAPISessionFeature->SetReceiveSessionPayloadBinding(FOnReceiveNativePayload());
		NativeAPISessionFeature->EndSession();
	}
}

void UNativeAPISubsystem::HandleOnReceiveNativePayload(const FNativeAPIPayload& InPayload)
{
	if (!InPayload.IsValid())
	{
		return;
	}

	FNativeAPIPayload TempPayload = InPayload;
	TArray<FNativeAPIPayload> ExecutePayloads;
#if WITH_EDITOR

	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		if (WorldContext.WorldType == EWorldType::PIE)
		{
			TempPayload.FixupFromPIE(WorldContext.PIEInstance);
			ExecutePayloads.Add(TempPayload);
		}
	}

#else
	ExecutePayloads.Add(InPayload);
#endif

	for (auto Payload : ExecutePayloads)
	{
		ProcessingNativeAPI(Payload);
	}
}
