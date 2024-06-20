// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticFunctions/StaticFunctions_Asset.h"

#include "AssetToolsModule.h"
#include "EditorUtilityLibrary.h"
#include "FileHelpers.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"

FAssetData FStaticFunctions_Asset::GetAssetData(const UObject* InAsset)
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
	return AssetRegistryModule.Get().GetAssetByObjectPath(InAsset->GetPathName());
}

TArray<FAssetData> FStaticFunctions_Asset::GetAssetsDataByPath(const FString& InAssetPackagePath)
{
	TArray<FAssetData> AssetsData;
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByPath(FName(InAssetPackagePath), AssetsData);

	return AssetsData;
}

FName FStaticFunctions_Asset::GetAssetPackagePath(const UObject* InAsset)
{
	const FAssetData AssetData = GetAssetData(InAsset);
	return AssetData.PackagePath;
}

FPackagePath FStaticFunctions_Asset::GetAssetPackageName(const UObject* InAsset)
{
	const FAssetData AssetData = GetAssetData(InAsset);

	FPackagePath PackagePath;
	FPackagePath::TryFromPackageName(AssetData.PackageName, PackagePath);

	return PackagePath;
}

FString FStaticFunctions_Asset::GetAssetLocalFullPath(const UObject* InAsset)
{
	const FPackagePath PackagePath = GetAssetPackageName(InAsset);

	if (PackagePath.IsEmpty())
	{
		return {};
	}

	return PackagePath.GetLocalFullPath();
}

FString FStaticFunctions_Asset::GetAssetFullPath(const UObject* InAsset)
{
	return FPaths::ConvertRelativePathToFull(GetAssetLocalFullPath(InAsset));
}

FString FStaticFunctions_Asset::GetAssetFullDirectoryPath(const UObject* InAsset)
{
	const FString FullPath = GetAssetFullPath(InAsset);
	FString FullDirectoryPath;
	FullPath.Split("/", &FullDirectoryPath, nullptr, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

	return FullDirectoryPath;
}

FString FStaticFunctions_Asset::GetAssetExtension(const UObject* InAsset)
{
	return FPaths::GetExtension(GetAssetFullPath(InAsset));
}

FString FStaticFunctions_Asset::CreateUniqueAssetName(FString InPackageName, FString InSuffix)
{
	FString PackageName;
	FString AssetName;

	const FAssetToolsModule& AssetToolsModule = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools");
	AssetToolsModule.Get().CreateUniqueAssetName(InPackageName, InSuffix, PackageName, AssetName);

	return AssetName;
}

void FStaticFunctions_Asset::RenameAsset(UObject* InAsset, FString NewName)
{
	FString UniqueAssetName = NewName;
	if (FPaths::FileExists(GetAssetFullDirectoryPath(InAsset) + "/" + NewName + "." + GetAssetExtension(InAsset)))
	{
		const FString AssetPackageName = GetAssetPackagePath(InAsset).ToString() + "/" + UniqueAssetName;
		UniqueAssetName = CreateUniqueAssetName(AssetPackageName);
	}

	UEditorUtilityLibrary::RenameAsset(InAsset, UniqueAssetName);

	SaveAsset(InAsset);
	FixupAssetReferencer(InAsset);
}

bool FStaticFunctions_Asset::SaveAsset(const UObject* InAsset)
{
	if (UPackage* Package = FindPackage(nullptr, *FPackageName::FilenameToLongPackageName(InAsset->GetPathName())))
	{
		Package->SetDirtyFlag(true);
		return FEditorFileUtils::SaveDirtyPackages(false, false, true);
	}

	return false;
}

FEditorFileUtils::EPromptReturnCode FStaticFunctions_Asset::SaveAssets(TArray<UObject*> InAssets)
{
	TArray<UPackage*> PackagesToSave;

	for (const auto Asset : InAssets)
	{
		if (UPackage* Package = FindPackage(nullptr, *FPackageName::FilenameToLongPackageName(Asset->GetPathName())))
		{
			PackagesToSave.Add(Package);
		}
	}

	return FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, false, false);
}

FEditorFileUtils::EPromptReturnCode FStaticFunctions_Asset::SaveAssetsAndFixupReferencer(TArray<UObject*> InAssets)
{
	const FEditorFileUtils::EPromptReturnCode ReturnCode = SaveAssets(InAssets);
	FixupAssetsReferencer(InAssets);

	return ReturnCode;
}

void FStaticFunctions_Asset::DeleteAsset(UObject* InAsset)
{
	DeleteAssets(TArray<UObject*>{ InAsset });
}

void FStaticFunctions_Asset::DeleteAssets(TArray<UObject*> InAssets)
{
	ObjectTools::DeleteObjectsUnchecked(InAssets);
}

void FStaticFunctions_Asset::FixupAssetReferencer(UObject* InAsset)
{
	TArray<UObjectRedirector*> ObjectRedirector;
	if (UObjectRedirector* RedirectorToFix = Cast<UObjectRedirector>(InAsset))
	{
		ObjectRedirector.Add(RedirectorToFix);
	}

	const FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	AssetToolsModule.Get().FixupReferencers(ObjectRedirector);
}

void FStaticFunctions_Asset::FixupAssetsReferencer(TArray<UObject*> InAssets)
{
	TArray<UObjectRedirector*> ObjectRedirector;
	for (const auto Object : InAssets)
	{
		if (UObjectRedirector* RedirectorToFix = Cast<UObjectRedirector>(Object))
		{
			ObjectRedirector.Add(RedirectorToFix);
		}
	}

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	AssetToolsModule.Get().FixupReferencers(ObjectRedirector);
}
