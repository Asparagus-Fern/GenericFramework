// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GDALDate.h"
#include "GDALType.h"
#include "Subsystems/EngineSubsystem.h"
#include "GDALSubsystem.generated.h"

class UGDALDate;

/**
 * 
 */
UCLASS()
class UNREALGDAL_API UGDALSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintCallable)
	void Test();

public:
	template <typename T>
	T* LoadGDALDate(const FString& InPath)
	{
		/* 检查驱动是否初始化 */
		const GDALDriverH oDriver = GDALGetDriverByName("ESRI Shapefile");
		if (oDriver == nullptr)
		{
			FMessageLog("驱动没有初始化").Warning(FText::FromString("\n"));
			return nullptr;
		}

		/* 检查是否存在缓存 */
		if (UGDALDate** Found = GDALDateArr.FindByPredicate([InPath](const UGDALDate* GDALData)
			{
				return InPath == GDALData->GetDataPath();
			}
		))
		{
			return Cast<T>(*Found);
		}

		if (GDALDataset* DataSource = static_cast<GDALDataset*>(GDALOpenEx(TCHAR_TO_UTF8(*InPath), GDAL_OF_VECTOR, NULL, NULL, NULL)))
		{
			T* NewGDALData = NewObject<T>(this);
			NewGDALData->Initialize(InPath, DataSource);
			GDALDateArr.Add(NewGDALData);

			return NewGDALData;
		}

		return nullptr;
	}

protected:
	UPROPERTY()
	TArray<UGDALDate*> GDALDateArr;
};
