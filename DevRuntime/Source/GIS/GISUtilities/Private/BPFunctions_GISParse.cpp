// Fill out your copyright notice in the Description page of Project Settings.

#include "GeographicCoordinates.h"

#include "Windows/MinWindows.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"

#include "gdal_priv.h"
#include "ogrsf_frmts.h"

#include "Windows/PostWindowsApi.h"

#include "BPFunctions_GISParse.h"

#include "GeoReferencingSystem.h"
#include "Debug/DebugType.h"

FVector ConvertToEngineLocation(AGeoReferencingSystem* GeoReferencingSystem, OGRPoint* InPoint)
{
	const double x = InPoint->getX();
	const double y = InPoint->getY();

	FVector EngineLocation;
	GeoReferencingSystem->GeographicToEngine(FGeographicCoordinates(FVector(y, x, 10000.0f)), EngineLocation);

	return EngineLocation;
}

bool UBPFunctions_GISParse::ParseSHPAsPoint(AGeoReferencingSystem* MyGeoReferencing, const FString& SHPPath, TArray<FVector>& PointCoordinates)
{
	// 注册所有的驱动
	GDALAllRegister();

	// 为了支持中文路径，请添加下面这句代码
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "YES");

	// 为了使属性表字段支持中文，请添加下面这句
	//CPLSetConfigOption("SHAPE_ENCODING","CP936");

	//读取数据，这里以ESRI的shp文件为例
	FString strDriverName = "ESRI Shapefile";

	//创建一个文件，根据strDriverName扩展名自动判断驱动类型
	//   Driver oDriver =GetDriverByName(strDriverName);
	// GDALDriver oDriver=GDALGetDriverByName(TEXT("strDriverName"));
	GDALDriverH oDriver = GDALGetDriverByName("ESRI Shapefile");
	if (oDriver == NULL)
	{
		// System.out.println(strDriverName+ "驱动没有初始化");
		FMessageLog("驱动没有初始化").Warning(FText::FromString("\n"));
		return false;
	}

	// 读取shp文件
	//DataSource srcDataSource = ogr.Open(srcFile, 0);
	GDALDataset* DataSource = static_cast<GDALDataset*>(GDALOpenEx(TCHAR_TO_UTF8(*SHPPath), GDAL_OF_VECTOR, NULL, NULL, NULL));

	if (DataSource == NULL)
	{
		FMessageLog("Log").Error(FText::FromString(TEXT("文件读取错误") + CPLGetLastErrorNo()));
		FMessageLog("Log").Error(FText::FromString(TEXT("Open failed") + CPLGetLastErrorNo()));
		return false;
	}

	//获取该数据源中的图层个数，如果小于1返回错误，shp只有一个图层，mdb会有多个
	const int layerCount = DataSource->GetLayerCount();
	FMessageLog(TEXT("图层数 = ")).Error(FText::FromString("\n" + layerCount));
	if (layerCount < 1)
	{
		FMessageLog(TEXT("异常：")).Error(FText::FromString("没有图层\n"));
		return false;
	}

	for (int i = 0; i < layerCount; ++i)
	{
		OGRLayer* Layer = DataSource->GetLayer(i);
		if (Layer == nullptr)
		{
			// 处理图层获取失败的情况
			continue;
		}

		Layer->ResetReading();

		for (auto FeatureIt = 0; FeatureIt < Layer->GetFeatureCount(); FeatureIt++)
		{
			OGRFeature* Feature = Layer->GetFeature(FeatureIt);

			OGRGeometry* Geometry = Feature->GetGeometryRef();
			OGRwkbGeometryType GeometryType = Geometry->getGeometryType();

			if (Geometry != nullptr && wkbFlatten(GeometryType) == wkbPoint)
			{
				if (OGRPoint* Point = static_cast<OGRPoint*>(Geometry))
				{
					PointCoordinates.Add(ConvertToEngineLocation(MyGeoReferencing, Point));
				}
			}

			OGRFeature::DestroyFeature(Feature);
		}
	}

	GDALClose(DataSource);

	return true;
}

bool UBPFunctions_GISParse::ParseSHPAsLine(AGeoReferencingSystem* MyGeoReferencing, const FString& SHPPath, TArray<FLineCoordinate>& LineCoordinates)
{
	// 注册所有的驱动
	GDALAllRegister();

	// 为了支持中文路径，请添加下面这句代码
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "YES");

	// 为了使属性表字段支持中文，请添加下面这句
	//CPLSetConfigOption("SHAPE_ENCODING","CP936");

	//读取数据，这里以ESRI的shp文件为例
	FString strDriverName = "ESRI Shapefile";

	//创建一个文件，根据strDriverName扩展名自动判断驱动类型
	//   Driver oDriver =GetDriverByName(strDriverName);
	// GDALDriver oDriver=GDALGetDriverByName(TEXT("strDriverName"));
	GDALDriverH oDriver = GDALGetDriverByName("ESRI Shapefile");
	if (oDriver == NULL)
	{
		// System.out.println(strDriverName+ "驱动没有初始化");
		FMessageLog("驱动没有初始化").Warning(FText::FromString("\n"));
		return false;
	}

	// 读取shp文件
	//DataSource srcDataSource = ogr.Open(srcFile, 0);
	GDALDataset* DataSource = static_cast<GDALDataset*>(GDALOpenEx(TCHAR_TO_UTF8(*SHPPath), GDAL_OF_VECTOR, NULL, NULL, NULL));

	if (DataSource == NULL)
	{
		FMessageLog("Log").Error(FText::FromString(TEXT("文件读取错误") + CPLGetLastErrorNo()));
		FMessageLog("Log").Error(FText::FromString(TEXT("Open failed") + CPLGetLastErrorNo()));
		return false;
	}

	//获取该数据源中的图层个数，如果小于1返回错误，shp只有一个图层，mdb会有多个
	const int layerCount = DataSource->GetLayerCount();
	FMessageLog(TEXT("图层数 = ")).Error(FText::FromString("\n" + layerCount));
	if (layerCount < 1)
	{
		FMessageLog(TEXT("异常：")).Error(FText::FromString("没有图层\n"));
		return false;
	}

	for (int i = 0; i < layerCount; ++i)
	{
		OGRLayer* Layer = DataSource->GetLayer(i);
		if (Layer == nullptr)
		{
			// 处理图层获取失败的情况
			continue;
		}

		Layer->ResetReading();

		for (auto FeatureIt = 0; FeatureIt < Layer->GetFeatureCount(); FeatureIt++)
		{
			OGRFeature* Feature = Layer->GetFeature(FeatureIt);

			// for (int FieldIt = 0; FieldIt < Feature->GetFieldCount(); FieldIt++)
			// {
			// 	DLOG(DLogDefault, Log, TEXT("Index : %d, Field : %hs"), Feature->GetFieldCount(), Feature->GetFieldAsString(FieldIt))
			// }

			OGRGeometry* Geometry = Feature->GetGeometryRef();
			OGRwkbGeometryType GeometryType = Geometry->getGeometryType();

			if (Geometry != nullptr && wkbFlatten(GeometryType) == wkbLineString)
			{
				if (const OGRLineString* Line = static_cast<OGRLineString*>(Geometry))
				{
					OGRPoint* StartPoint = new OGRPoint();
					OGRPoint* EndPoint = new OGRPoint();

					Line->StartPoint(StartPoint);
					Line->EndPoint(EndPoint);

					FLineCoordinate LineCoordinate;

					LineCoordinate.StartPointCoordinate = ConvertToEngineLocation(MyGeoReferencing, StartPoint);
					LineCoordinate.EndPointCoordinate = ConvertToEngineLocation(MyGeoReferencing, EndPoint);

					LineCoordinates.Add(LineCoordinate);
				}
			}

			OGRFeature::DestroyFeature(Feature);
		}
	}

	GDALClose(DataSource);

	return true;
}
