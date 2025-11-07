// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "BPFunctions/BPFunctions_Android.h"

#if PLATFORM_ANDROID
#include "AndroidPermissionFunctionLibrary.h"
#endif

const FString UnrealGameFileName = TEXT("UnrealGame/");

FString UBPFunctions_Android::GetAndroidRootDir()
{
#if PLATFORM_ANDROID
	if (!UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.READ_EXTERNAL_STORAGE")))
	{
		UAndroidPermissionFunctionLibrary::AcquirePermissions({TEXT("android.permission.READ_EXTERNAL_STORAGE")});
	}
	
	return TEXT("/sdcard/");
#else
	return TEXT("");
#endif
}

FString UBPFunctions_Android::GetAndroidProjectDir(bool bUseExternalStorage)
{
#if PLATFORM_ANDROID
	if (bUseExternalStorage && !UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.READ_EXTERNAL_STORAGE")))
	{
		UAndroidPermissionFunctionLibrary::AcquirePermissions({TEXT("android.permission.READ_EXTERNAL_STORAGE")});
	}
	
	return bUseExternalStorage ? FPaths::Combine(GetAndroidRootDir(), UnrealGameFileName, FApp::GetProjectName()) : FPaths::ProjectDir();
#else
	return FPaths::ProjectDir();
#endif
}

FString UBPFunctions_Android::GetAndroidConfigDir(bool bUseExternalStorage)
{
#if PLATFORM_ANDROID
	if (bUseExternalStorage && !UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.READ_EXTERNAL_STORAGE")))
	{
		UAndroidPermissionFunctionLibrary::AcquirePermissions({TEXT("android.permission.READ_EXTERNAL_STORAGE")});
	}
	
	return bUseExternalStorage ? FPaths::Combine(GetAndroidProjectDir, TEXT("Config/")) : FPaths::ProjectConfigDir();
#else
	return FPaths::ProjectConfigDir();
#endif
}

FString UBPFunctions_Android::GetAndroidContentDir(bool bUseExternalStorage)
{
#if PLATFORM_ANDROID
	if (bUseExternalStorage && !UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.READ_EXTERNAL_STORAGE")))
	{
		UAndroidPermissionFunctionLibrary::AcquirePermissions({TEXT("android.permission.READ_EXTERNAL_STORAGE")});
	}
	
	return bUseExternalStorage ? FPaths::Combine(GetAndroidProjectDir, TEXT("Content/")) : FPaths::ProjectContentDir();
#else
	return FPaths::ProjectContentDir();
#endif
}

FString UBPFunctions_Android::GetAndroidSavedDir(bool bUseExternalStorage)
{
#if PLATFORM_ANDROID
	if (bUseExternalStorage && !UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.READ_EXTERNAL_STORAGE")))
	{
		UAndroidPermissionFunctionLibrary::AcquirePermissions({TEXT("android.permission.READ_EXTERNAL_STORAGE")});
	}
	
	return bUseExternalStorage ? FPaths::Combine(GetAndroidProjectDir, TEXT("Saved/")) : FPaths::ProjectSavedDir();
#else
	return FPaths::ProjectSavedDir();
#endif
}
