// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "AsyncFunctions/Android/AcquireAndroidPermissionAsyncAction.h"

#if PLATFORM_ANDROID
#include "AndroidPermissionCallbackProxy.h"
#include "AndroidPermissionFunctionLibrary.h"
#endif

void UAcquireAndroidPermissionAsyncAction::Activate()
{
	Super::Activate();

#if PLATFORM_ANDROID
	if (Permissions.IsEmpty())
	{
		FFrame::KismetExecutionMessage(TEXT("Check Android Permission Must Provide a Permission String."), ELogVerbosity::Error);
		return;
	}

	for (auto& Permission : Permissions)
	{
		if (!UAndroidPermissionFunctionLibrary::CheckPermission(Permission))
		{
			PermissionsNotAcquired.Add(Permission);
		}
	}

	UAndroidPermissionCallbackProxy::GetInstance()->OnPermissionsGrantedDelegate.AddUObject(this, &UAcquireAndroidPermissionAsyncAction::OnPermissionsGranted);
	UAndroidPermissionFunctionLibrary::AcquirePermissions(PermissionsNotAcquired);
#endif
}

UAcquireAndroidPermissionAsyncAction* UAcquireAndroidPermissionAsyncAction::AsyncAcquireAndroidPermission(const FString& InPermission)
{
	UAcquireAndroidPermissionAsyncAction* NewAction = NewObject<UAcquireAndroidPermissionAsyncAction>();
	NewAction->Permissions.Add(InPermission);
	return NewAction;
}

UAcquireAndroidPermissionAsyncAction* UAcquireAndroidPermissionAsyncAction::AsyncAcquireAndroidPermissions(const TArray<FString>& InPermissions)
{
	UAcquireAndroidPermissionAsyncAction* NewAction = NewObject<UAcquireAndroidPermissionAsyncAction>();
	NewAction->Permissions = InPermissions;
	return NewAction;
}

void UAcquireAndroidPermissionAsyncAction::OnPermissionsGranted(const TArray<FString>& InPermissions, const TArray<bool>& InGrantResults)
{
#if PLATFORM_ANDROID
	UAndroidPermissionCallbackProxy::GetInstance()->OnPermissionsGrantedDelegate.RemoveAll(this);

	for (int i = 0; i < InGrantResults.Num(); ++i)
	{
		if (InGrantResults[i])
		{
			continue;
		}

		FailPermissions.Add(InPermissions[i]);
	}

	if (FailPermissions.IsEmpty())
	{
		OnSuccess.Broadcast();
	}
	else
	{
		OnFail.Broadcast(FailPermissions);
	}
#endif
}
