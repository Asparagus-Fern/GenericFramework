// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
// #include "ProcedureFlowType.generated.h"

PROCEDUREFLOWSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(GenericLogProcedureFlow, Log, All);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_Initialize);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_Load);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_LoadLevelStreaming);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_LoadPartitionedWorld);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_InitializeFinish);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_Play);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_Deinitialize);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow_DeinitializeFinish);
