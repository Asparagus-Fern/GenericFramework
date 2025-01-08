// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_BlueprintEditor.h"

#include "BlueprintEditor.h"
#include "BlueprintEditorModule.h"

TSharedPtr<FBlueprintEditor> UBPFunctions_BlueprintEditor::GetBlueprintEditor(const UBlueprint* InBlueprint)
{
	const FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
	for (auto& BlueprintEditor : BlueprintEditorModule.GetBlueprintEditors())
	{
		TSharedRef<FBlueprintEditor> Editor = StaticCastSharedRef<FBlueprintEditor>(BlueprintEditor);
		if (Editor->GetBlueprintObj() == InBlueprint)
		{
			return Editor;
		}
	}

	return nullptr;
}
