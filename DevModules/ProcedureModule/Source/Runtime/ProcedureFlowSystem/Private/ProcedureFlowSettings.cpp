// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ProcedureFlowSettings.h"

#include "GameplayTagsSettings.h"

UProcedureFlowSettings::UProcedureFlowSettings(const FObjectInitializer& ObjectInitializer)
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
