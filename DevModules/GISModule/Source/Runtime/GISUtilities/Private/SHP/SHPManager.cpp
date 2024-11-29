// Fill out your copyright notice in the Description page of Project Settings.


#include "SHP/SHPManager.h"

#include "BPFunctions/BPFunctions_File.h"
#include "GeoReferencingSystem.h"
#include "Debug/DebugType.h"

#include "Windows/PreWindowsApi.h"
#include "gdal_priv.h"
#include "ogrsf_frmts.h"
#include "Windows/PostWindowsApi.h"

/* ==================== FSHPReferencing ==================== */

FSHPReference::FSHPReference()
{
}

// FSHPReference::FSHPReference(AGeoReferencingSystem* InGeoReferencing, USHPHandle* InSHPHandles)
// 	: GeoReferencingSystem(InGeoReferencing),
// 	  SHPHandle(InSHPHandles)
// {
// }

/* ==================== USHPManager ==================== */

bool USHPManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void USHPManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void USHPManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

void USHPManager::Test(AGeoReferencingSystem* GeoReferencing)
{
	// TArray<USHPHandle*> TempSHPHandles;
	// LoadSHP(GeoReferencing, TempSHPHandles);

	// for (const auto& SHPHandle : TempSHPHandles)
	// {
	// 	SHPHandle->GetSHPLayerHandleByName(TEXT("你好"));
	// }
}

GDALDataset* USHPManager::LoadSHPDateSource(AGeoReferencingSystem* GeoReferencingSystem, const FString& SHPPath)
{
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
		return nullptr;
	}

	// 读取shp文件
	GDALDataset* DataSource = static_cast<GDALDataset*>(GDALOpenEx(TCHAR_TO_UTF8(*SHPPath), GDAL_OF_VECTOR, NULL, NULL, NULL));

	
	return DataSource;
}

// bool USHPManager::LoadSHP(AGeoReferencingSystem* GeoReferencingSystem, TArray<USHPHandle*>& OutSHPHandles)
// {
// 	TArray<FString> FilePaths;
// 	if (UBPFunctions_File::OpenFileDialog("shp", FilePaths))
// 	{
// 		for (auto& FilePath : FilePaths)
// 		{
// 			if (GDALDataset* DataSource = LoadSHPDateSource(GeoReferencingSystem, FilePath))
// 			{
// 				if (USHPHandle* NewSHPHandle = MakeSHPHandle(GeoReferencingSystem, DataSource))
// 				{
// 					OutSHPHandles.Add(NewSHPHandle);
// 					SHPReferences.Add(FSHPReference(GeoReferencingSystem, NewSHPHandle));
// 				}
// 			}
// 		}
// 	}
//
// 	return false;
// }
//
// USHPHandle* USHPManager::MakeSHPHandle(AGeoReferencingSystem* GeoReferencingSystem, GDALDataset* DataSource)
// {
// 	if (!IsValid(GeoReferencingSystem) || !DataSource)
// 	{
// 		return nullptr;
// 	}
//
// 	USHPHandle* SHPHandle = NewObject<USHPHandle>(GeoReferencingSystem);
// 	SHPHandle->SetOwnerGeoReferencing(GeoReferencingSystem);
// 	SHPHandle->SetDataSource(DataSource);
//
// 	if (SHPHandle->ShouldCreateHandle())
// 	{
// 		SHPHandle->NativeOnCreate();
// 		return SHPHandle;
// 	}
//
// 	return nullptr;
// }
