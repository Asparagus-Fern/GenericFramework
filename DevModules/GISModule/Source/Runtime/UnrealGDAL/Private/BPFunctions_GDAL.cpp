// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions_GDAL.h"

#include "GDALDate.h"
#include "GDALFeature.h"
#include "GDALSubsystem.h"

#define LOCTEXT_NAMESPACE "BPFunctions_GDAL"

UGDALDate* UBPFunctions_GDAL::LoadGDALData(FString InPath, const TSubclassOf<UGDALDate> InClass)
{
	ensure(InClass);

	if (UGDALSubsystem* GDALSubsystem = GEngine->GetEngineSubsystem<UGDALSubsystem>())
	{
		return GDALSubsystem->LoadGDALDate<UGDALDate>(InPath);
	}

	return nullptr;
}

FVector UBPFunctions_GDAL::ConvGeoCoordinateToEngineLocation(AGeoReferencingSystem* GeoReferencingSystem, FVector InCoordinate)
{
	FVector EngineLocation;
	GeoReferencingSystem->GeographicToEngine(FGeographicCoordinates(FVector(InCoordinate.Y, InCoordinate.X, InCoordinate.Z)), EngineLocation);

	return EngineLocation;
}

DEFINE_FUNCTION(UBPFunctions_GDAL::execGetGDALField)
{
	P_GET_OBJECT_REF(UGDALFeature, Feature);
	P_GET_PROPERTY(FStrProperty, FieldName);

	Stack.StepCompiledIn<FProperty>(nullptr);
	FProperty* ValueProp = Stack.MostRecentProperty;
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;

	if (!ValueProp || !ValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			LOCTEXT("GetField_MissingOutputProperty", "Failed to resolve the output parameter for GetField.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}

	bool bResult = false;

	P_NATIVE_BEGIN
		// bResult = GDALFieldToProperty(Feature, FieldName, ValueProp, ValuePtr);
	P_NATIVE_END

	*static_cast<bool*>(RESULT_PARAM) = bResult;
}

bool UBPFunctions_GDAL::GDALFieldToProperty(UGDALFeature* InFeature, const FString& InFieldName, const FProperty* TargetProperty, void* TargetValuePtr)
{
	// check(TargetProperty && TargetValuePtr);
	//
	// if (OGRFeature* Feature = InFeature->GetDataSource())
	// {
	// 	for (auto FieldIt = 0; FieldIt < Feature->GetFieldCount(); FieldIt++)
	// 	{
	// 		const OGRFieldDefn* FieldDefn = Feature->GetFieldDefnRef(FieldIt);
	// 		if (UTF8_TO_TCHAR(FieldDefn->GetNameRef()) == InFieldName)
	// 		{
	// 			const OGRFieldType FieldType = FieldDefn->GetType();
	// 			const bool Success = ConvToProperty(Feature, FieldType, FieldIt, TargetValuePtr);
	//
	// 			if (Success)
	// 			{
	// 				TargetProperty->SetValue_InContainer(nullptr, TargetValuePtr);
	// 			}
	//
	// 			return Success;
	// 		}
	// 	}
	// }

	return false;
}

#undef LOCTEXT_NAMESPACE
