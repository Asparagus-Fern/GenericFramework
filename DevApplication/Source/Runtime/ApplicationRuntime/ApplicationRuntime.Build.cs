using UnrealBuildTool;

public class ApplicationRuntime : ModuleRules
{
	public ApplicationRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
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

				/* Dev Misc */
				"UnrealMisc",

				/* Dev Module */
				"CameraSystem",
				"GenericJson",
				"GenericProtocol",
				"EventUtilities",
				"GenericGameplaySystem",
				"PlayerInputUtilities",
				"ExternalData",
				"NativeAPI",
				"MovieSceneUtilities",
				"LevelSequenceSystem",
				"MediaSystem",
				"ProcedureFlowSystem",
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
				"UltraDynamicSkyUtilities",
			}
		);
	}
}