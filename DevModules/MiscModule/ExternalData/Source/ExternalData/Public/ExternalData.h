// Copyright ChenTaiye 2025,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "Engine/DataAsset.h"
#include "StructUtils/InstancedStruct.h"
#include "ExternalData.generated.h"

class FObjectPostSaveRootContext;

/**
 * 
 */
UCLASS(MinimalAPI, BlueprintType)
class UExternalData : public UDataAsset
{
	GENERATED_BODY()

public:
	// todo : 资产移除需移除对应的 .json 文件. 扩展该类资源对象, 我们需要提供一些快捷工作, 比如在编辑器刷新.
	UExternalData();

	// Begin UObject Interface.
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext) override;
	// virtual void PostRename(UObject* OldOuter, const FName OldName) override;
	// virtual void BeginDestroy() override;
#endif
	// 	// End UObject Interface.

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

	template <typename T>
	const T& GetData(bool bReload = true)
	{
		if (bReload)
		{
			ensureAlways(LoadData());
		}

		return RowStruct.Get<T>();
	}

	EXTERNALDATA_API static FString GetJsonFilePath(const FString& InName);
	EXTERNALDATA_API bool LoadData();
	EXTERNALDATA_API bool SaveData() const;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = Data)
	FInstancedStruct RowStruct;

	friend class UBPFunctions_ExternalData;
};
