// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FileHelpers.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Asset.generated.h"

/**
 * 
 */
UCLASS()
class DEVEDCORE_API UBPFunctions_Asset : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FAssetData GetAssetData(const UObject* InAsset);
	static TArray<FAssetData> GetAssetsDataByPath(const FString& InAssetPackagePath);
	
	static FName GetAssetPackagePath(const UObject* InAsset); /*  /LayerWidget/MenuInfo  */
	static FPackagePath GetAssetPackageName(const UObject* InAsset); /*  /LayerWidget/MenuInfo/ccc  */
	static FString GetAssetLocalFullPath(const UObject* InAsset); /*  ../../../../../UEProject/DevProject/Plugins/DevPlugin/Runtime/LayerWidget/Content/MenuInfo/cccd.uasset  */
	static FString GetAssetFullPath(const UObject* InAsset); /*  C:/UEProject/DevProject/Plugins/DevPlugin/Runtime/LayerWidget/Content/MenuInfo/cccd.uasset"  */
	static FString GetAssetFullDirectoryPath(const UObject* InAsset); /*  "C:/UEProject/DevProject/Plugins/DevPlugin/Runtime/LayerWidget/Content/MenuInfo"  */

	static FString GetAssetExtension(const UObject* InAsset);

	static FString CreateUniqueAssetName(FString InPackageName, FString InSuffix = "");
	static void RenameAsset(UObject* InAsset, FString NewName);

	static bool SaveAsset(const UObject* InAsset);
	static FEditorFileUtils::EPromptReturnCode SaveAssets(TArray<UObject*> InAssets);
	static FEditorFileUtils::EPromptReturnCode SaveAssetsAndFixupReferencer(TArray<UObject*> InAssets);

	static void DeleteAsset(UObject* InAsset);
	static void DeleteAssets(TArray<UObject*> InAssets);

	static void FixupAssetReferencer(UObject* InAsset);
	static void FixupAssetsReferencer(TArray<UObject*> InAssets);
};
