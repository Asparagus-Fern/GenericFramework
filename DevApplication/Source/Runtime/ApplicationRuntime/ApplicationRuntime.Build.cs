using UnrealBuildTool;

public class ApplicationRuntime : ModuleRules
{
	public ApplicationRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc",
				"DevCore",

				"Niagara",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				/* Unreal Engine */
				"ModularGameplay",
				"GameplayTags",
				"UMG",
				"LevelSequence",
				"MovieScene",
				"MediaAssets",

				"NiagaraCore",


				/* Dev Module */
				"GenericCameraSystem",
				"GenericJson",
				"GenericProtocol",
				"NativeAPI",
				"ExternalData",
				"GenericGameplaySystem",
				"GenericGameSettingSystem",
				"GenericSaveGameSystem",
				"GenericInputSystem",
				"ExternalData",
				"GenericMovieSceneSystem",
				"LevelSequenceSystem",
				"MediaSystem",
				"ProcedureFlowSystem",
				"PropertySystem",
				"GenericThreadSystem",
				"ExtraProc",
				"WidgetGeneration",
				"WidgetGroupGeneration",
				"WorldWidgetGeneration",
				"WidgetApplication",
				"WorldUtilities",
				"LevelStreaming",
				"WorldPartition",

				/* Marketplace */
				"DBTween",
				"UltraDynamicSkyUtilities"
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}