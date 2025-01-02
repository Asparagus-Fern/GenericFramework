// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlowSetting.h"

#include "GameplayTagsSettings.h"

UProcedureFlowSetting::UProcedureFlowSetting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (UGameplayTagsSettings* GameplayTagsSettings = GetMutableDefault<UGameplayTagsSettings>())
	{
		if (const UDataTable* ProcedureFlowTagTable = LoadObject<UDataTable>(nullptr,TEXT("/Script/Engine.DataTable'/ProcedureModule/DataTable/DT_ProcedureFlow_Main.DT_ProcedureFlow_Main'")))
		{
			if (!GameplayTagsSettings->GameplayTagTableList.Contains(ProcedureFlowTagTable->GetPathName()))
			{
				GameplayTagsSettings->GameplayTagTableList.Add(FSoftObjectPath(ProcedureFlowTagTable));
			}
		}
	}
}
