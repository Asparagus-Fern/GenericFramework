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
				"DevCore"
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
				
				/* Dev Module */
				"CameraSystem",
				"GenericJson",
				"GenericProtocol",
				"EventUtilities",
				"GenericGameplaySystem",
				"GenericGameSettingSystem",
				"GenericSaveGameSystem",
				"PlayerInputUtilities",
				"ExternalData",
				"NativeAPI",
				"MovieSceneUtilities",
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
	}
}