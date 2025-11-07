// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions/BPFunctions_File.h"

#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Interfaces/IPluginManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/Paths.h"
#include "Type/AndroidType.h"
#include "Type/GenericType.h"

#if WITH_EDITOR
#include "EditorDirectories.h"
#endif

#define LOCTEXT_NAMESPACE "FUnrealMiscModule"

bool UBPFunctions_File::ExistDirectory(const FString& Directory)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.DirectoryExists(*Directory);
}

bool UBPFunctions_File::CreateDirectory(const FString& Directory)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.CreateDirectoryTree(*Directory);
}

bool UBPFunctions_File::DeleteDirectory(const FString& Directory)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.DeleteDirectory(*Directory);
}

bool UBPFunctions_File::DeleteDirectoryRecursively(const FString& Directory)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	return PlatformFile.DeleteDirectoryRecursively(*Directory);
}

bool UBPFunctions_File::OpenDirectoryDialog(FString& AbsoluteDirectoryPath)
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform != nullptr)
	{
		FString DefaultPath;

#if WITH_EDITOR
		DefaultPath = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_OPEN);
#endif

		TArray<FString> OpenFiles;
		if (DesktopPlatform->OpenDirectoryDialog(
			FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
			LOCTEXT("OpenDirectoryDialogTitle", "Choose a Directory").ToString(),
			DefaultPath,
			AbsoluteDirectoryPath
		))
		{
			return true;
		}
	}

	return false;
}

bool UBPFunctions_File::GetPluginBaseDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir();
		return true;
	}
	return false;
}

bool UBPFunctions_File::GetPluginBinariesDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Binaries";
		return true;
	}
	return false;
}

bool UBPFunctions_File::GetPluginContentDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetContentDir();
		return true;
	}
	return false;
}

bool UBPFunctions_File::GetPluginIntermediateDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Intermediate";
		return true;
	}
	return false;
}

bool UBPFunctions_File::GetPluginResourcesDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Resources";
		return true;
	}
	return false;
}

bool UBPFunctions_File::GetPluginSourceDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Source";
		return true;
	}
	return false;
}

bool UBPFunctions_File::GetPluginExtraDir(const FString& InPluginName, FString& Directory)
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(InPluginName))
	{
		Directory = Plugin->GetBaseDir() + "/Extra";
		return true;
	}
	return false;
}

TArray<FString> UBPFunctions_File::FindFiles(const FString& AbsoluteDirectoryPath, const FString& Extension)
{
	TArray<FString> Result;
	IFileManager::Get().FindFiles(Result, *AbsoluteDirectoryPath, *Extension);
	return Result;
}

TArray<FString> UBPFunctions_File::FindFilesRecursive(const FString& AbsoluteDirectoryPath, const FString& Extension, const bool Files, const bool Directories, const bool bClearFileNames)
{
	TArray<FString> Result;
	IFileManager& FileManager = IFileManager::Get();
	if (FileManager.DirectoryExists(*AbsoluteDirectoryPath))
	{
		FileManager.FindFilesRecursive(Result, *AbsoluteDirectoryPath, *Extension, Files, Directories, bClearFileNames);
	}
	return Result;
}

bool UBPFunctions_File::ExistFile(const FString& FileName)
{
	return IFileManager::Get().FileExists(*FileName);
}

bool UBPFunctions_File::CopyFile(const FString FileSource, const FString FileDest, const bool Replace, const bool EvenIfReadOnly)
{
#if PLATFORM_ANDROID
	if (!UAndroidPermissionFunctionLibrary::CheckPermission(TEXT("android.permission.WRITE_EXTERNAL_STORAGE")))
	{
		UAndroidPermissionFunctionLibrary::AcquirePermissions({TEXT("android.permission.WRITE_EXTERNAL_STORAGE")});
	}
#endif
	return IFileManager::Get().Copy(*FileDest, *FileSource, Replace, EvenIfReadOnly) == COPY_OK;
}

bool UBPFunctions_File::MoveFile(const FString FileSource, const FString FileDest, const bool Replace, const bool EvenIfReadOnly)
{
	return IFileManager::Get().Move(*FileDest, *FileSource, Replace, EvenIfReadOnly);
}

bool UBPFunctions_File::DeleteFile(const FString FileName, const bool RequireExists, const bool EvenReadOnly)
{
	return IFileManager::Get().Delete(*FileName, RequireExists, EvenReadOnly);
}

bool UBPFunctions_File::IsFileReadOnly(const FString& FileName)
{
	return IFileManager::Get().IsReadOnly(*FileName);
}

FString UBPFunctions_File::ConvertToRelativePath(const FString& Filename)
{
	return IFileManager::Get().ConvertToRelativePath(*Filename);
}

int64 UBPFunctions_File::FileSize(const FString& Filename)
{
	return IFileManager::Get().FileSize(*Filename);
}

bool UBPFunctions_File::OpenFileDialog(FString FileType, TArray<FString>& FilePaths)
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform != nullptr)
	{
		FString DefaultPath;
		FString Filter;

		if (FileType.IsEmpty())
		{
			Filter = TEXT("All files (*.*)|*.*");
		}
		else
		{
			Filter = FString::Printf(TEXT("Choose %s Files (*.%s)|*.%s"), *FileType, *FileType, *FileType);
		}

#if WITH_EDITOR
		DefaultPath = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_OPEN);
#endif

		TArray<FString> OpenFiles;
		if (DesktopPlatform->OpenFileDialog(
			FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
			LOCTEXT("OpenFileDialogTitle", "Open File...").ToString(),
			DefaultPath,
			TEXT(""),
			Filter, //TEXT("Profile data (*.profViz) | *.profViz"),
			EFileDialogFlags::Multiple,
			OpenFiles
		))
		{
			for (auto& OpenFile : OpenFiles)
			{
				FilePaths.Add(FPaths::ConvertRelativePathToFull(OpenFile));
			}

#if WITH_EDITOR
			if (OpenFiles.IsValidIndex(0))
			{
				if (!OpenFiles[0].IsEmpty())
				{
					FEditorDirectories::Get().SetLastDirectory(ELastDirectory::GENERIC_OPEN, OpenFiles[0]);
				}
			}
#endif

			return true;
		}
	}

	return false;
}

bool UBPFunctions_File::SaveFileDialog(FString FileName, FString FileType, TArray<FString>& FilePaths)
{
	if (FileType.IsEmpty())
	{
		return false;
	}

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform != nullptr)
	{
		FString DefaultPath;
		const FString File = FString::Printf(TEXT("%s.%s"), *FileName, *FileType);
		const FString Filter = FString::Printf(TEXT("Save Files As (*.%s)|*.%s"), *FileType, *FileType);;

#if WITH_EDITOR
		DefaultPath = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_OPEN);
#endif

		TArray<FString> SaveFiles;
		if (DesktopPlatform->SaveFileDialog(
			FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
			LOCTEXT("SaveFileDialogTitle", "Save File...").ToString(),
			DefaultPath,
			File,
			Filter,
			EFileDialogFlags::None,
			SaveFiles
		))
		{
			for (auto& SaveFile : SaveFiles)
			{
				FilePaths.Add(FPaths::ConvertRelativePathToFull(SaveFile));
			}

			return true;
		}
	}

	return false;
}

#undef LOCTEXT_NAMESPACE
