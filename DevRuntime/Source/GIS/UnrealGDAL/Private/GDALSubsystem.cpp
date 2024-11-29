// Fill out your copyright notice in the Description page of Project Settings.


#include "GDALSubsystem.h"

#include "GDALDate.h"
#include "BPFunctions/BPFunctions_File.h"

bool UGDALSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGDALSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 注册所有的驱动
	GDALAllRegister();

	// 为了支持中文路径，请添加下面这句代码
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "YES");

	// 为了使属性表字段支持中文，请添加下面这句
	CPLSetConfigOption("SHAPE_ENCODING", "CP936");

	//创建一个文件，根据strDriverName扩展名自动判断驱动类型
	const GDALDriverH oDriver = GDALGetDriverByName("ESRI Shapefile");
	if (oDriver == nullptr)
	{
		FMessageLog("驱动没有初始化").Warning(FText::FromString("\n"));
	}
}

void UGDALSubsystem::Deinitialize()
{
	Super::Deinitialize();

	for (const auto& GDALDate : GDALDateArr)
	{
		GDALDate->Deinitialize();
	}
}

void UGDALSubsystem::Test()
{
	TArray<FString> FilePaths;
	if (UBPFunctions_File::OpenFileDialog("shp", FilePaths))
	{
		for (auto& FilePath : FilePaths)
		{
			if (UGDALDate* DataSource = LoadGDALDate<UGDALDate>(FilePath))
			{
				// DataSource->GetFileList();
			}
		}
	}
}
