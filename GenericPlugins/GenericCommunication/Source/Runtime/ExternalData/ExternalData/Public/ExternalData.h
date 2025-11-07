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
	UExternalData();

	// Begin UObject Interface.
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext) override;
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

	EXTERNALDATA_API FString GetJsonFilePath();
	EXTERNALDATA_API bool LoadData();
	EXTERNALDATA_API bool SaveData();

protected:
	UPROPERTY(EditAnywhere)
	FInstancedStruct RowStruct;

	friend class UBPFunctions_ExternalData;
};
