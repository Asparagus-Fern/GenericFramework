// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NativeAPIProxyComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "NativeAPILog.h"
#include "NativeAPITypes.h"
#include "NativeAPIUtilities.h"
#include "NativeAPIWorldSubsystem.h"
#include "Debug/DebugType.h"

FName UNativeAPIProxyComponent::NativeAPIProxyComponentDefaultName = TEXT("NativeAPIProxy");

UNativeAPIProxyComponent::UNativeAPIProxyComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  bProcessOnOwnerHidden(true)
{
	PrimaryComponentTick.bCanEverTick = false;
	bAutoRegister = true;

	const UClass* EntityClass = GetEntityClass();
	if (EntityClass != nullptr)
	{
		NativeAPIEntity.EntityClass = EntityClass->GetClassPathName().ToString();
	}
}

#if WITH_EDITOR
void UNativeAPIProxyComponent::PostInitProperties()
{
	Super::PostInitProperties();

	const AActor* Owner = GetOwner();

	if (Owner == nullptr)
		return;

	if (Owner->HasAnyFlags(RF_ClassDefaultObject | RF_Transient))
	{
		return;
	}

	const UClass* OwnerClass = Owner->GetClass();

	if (!OwnerClass || OwnerClass->HasAnyFlags(RF_Transient))
	{
		return;
	}

	const TSharedPtr<FJsonObject> APIJson = MakeShared<FJsonObject>();

	for (TFieldIterator<UFunction> FuncIt(OwnerClass); FuncIt; ++FuncIt)
	{
		if (!FNativeAPIUtilities::IsNativeAPIFunctionName(FuncIt->GetFName()))
		{
			continue;
		}

		TSharedPtr<FJsonValueObject> PropertyJson = MakeShared<FJsonValueObject>(FNativeAPIUtilities::WriteFunction(*FuncIt, OwnerClass->GetDefaultObject()));
		APIJson->SetField(FuncIt->GetName(), PropertyJson);
	}

	FString FuncJsonStr;
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&FuncJsonStr);
	FJsonSerializer::Serialize(APIJson.ToSharedRef(), JsonWriter, true);
	API = FuncJsonStr;
}
#endif

void UNativeAPIProxyComponent::OnRegister()
{
	Super::OnRegister();

	const UWorld* World = GetWorld();

#if WITH_EDITOR
	if (!World->IsGameWorld())
	{
		return;
	}
#endif

	UNativeAPIWorldSubsystem* NativeAPIWorldSubsystem = UNativeAPIWorldSubsystem::Get(World);

	if (NativeAPIWorldSubsystem != nullptr)
	{
		NativeAPIWorldSubsystem->RegisterNativeAPI(this);
	}
}

void UNativeAPIProxyComponent::OnUnregister()
{
	Super::OnUnregister();

	const UWorld* World = GetWorld();

#if WITH_EDITOR
	if (!World->IsGameWorld())
	{
		return;
	}
#endif

	UNativeAPIWorldSubsystem* NativeAPIWorldSubsystem = UNativeAPIWorldSubsystem::Get(World);

	if (NativeAPIWorldSubsystem != nullptr)
	{
		NativeAPIWorldSubsystem->UnRegisterNativeAPI(this);
	}
}

#if WITH_EDITOR
void UNativeAPIProxyComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	NativeAPIEntity.EntityClass = this->GetEntityClass()->GetClassPathName().ToString();
	NativeAPIEntity.EntityPath = this->GetEntityPath();
}

void UNativeAPIProxyComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	NativeAPIEntity.EntityClass.Empty();
	NativeAPIEntity.EntityPath.Empty();
}
#endif

void UNativeAPIProxyComponent::ProcessingNativeAPI(const FNativeAPIPayload& Payload) const
{
	if (!Payload.IsValid() || !Payload.IsConsumer(const_cast<ThisClass*>(this)))
	{
		return;
	}

	const UWorld* World = GetWorld();
	if (!World || !World->IsInitialized() || !World->HasBegunPlay())
	{
		return;
	}

	AActor* Owner = GetOwner();

	if (!IsValid(Owner) || !Owner->HasActorBegunPlay())
	{
		return;
	}

	if (Owner->IsHidden() && !bProcessOnOwnerHidden)
	{
		return;
	}

	TArray<FNativeAPITask> Tasks;
	Payload.GetTaskList(Tasks);

	for (auto Task : Tasks)
	{
		UFunction* Func = Owner->FindFunction(Task.FuncName);

		if (Func == nullptr)
		{
			continue;
		}

		bool bProcess = true;

		FStructOnScope FuncParams(Func);

		for (TFieldIterator<FProperty> It(Func); It && It->PropertyFlags & CPF_Parm; ++It)
		{
			void* ValuePtr = It->ContainerPtrToValuePtr<void*>(FuncParams.GetStructMemory());
			TSharedPtr<FJsonValue> Value = Task.ParamJson->TryGetField(It->GetName());

			// 在给定参数中没有找到 Property 字段, 我们应该终止此次调用, 并给出警告!
			if (!Value.IsValid())
			{
				bProcess = false;
				GenericLOG(LogNativeAPI, Error, TEXT("Procee Native API fail! Func [%s] there is no parameter named %s"), *Task.FuncName.ToString(), *It->GetName())
				break;
			}

			FNativeAPIUtilities::ReadValue(Value, *It, ValuePtr, Owner);
		}

		if (bProcess)
		{
			Owner->ProcessEvent(Func, FuncParams.GetStructMemory());
		}
	}
}

FString UNativeAPIProxyComponent::GetEntity() const
{
	if (NativeAPIEntity.Entity.IsEmpty())
	{
		return GetOwner()->GetClass()->GetName();
	}

	return NativeAPIEntity.Entity;
}

UClass* UNativeAPIProxyComponent::GetEntityClass() const
{
	const AActor* Owner = GetOwner();

	if (IsValid(Owner))
	{
		return Owner->GetClass();
	}

	return nullptr;
}

void UNativeAPIProxyComponent::SetProcessOnOwnerHiddenEnable(bool bEnable)
{
	if (bProcessOnOwnerHidden != bEnable)
	{
		bProcessOnOwnerHidden = bEnable;
	}
}
