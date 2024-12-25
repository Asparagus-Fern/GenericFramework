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

				"ModularGameplay",
				"GameplayTags",
				"UMG",
				"LevelSequence",
				"MovieScene",
				"MediaAssets",

				/* Dev Module */
				"EventUtilities",
				"DevGameplay",
				"ActiveNode",
				"ScreenWidgetGeneration",
				"WorldWidgetGeneration",
				"CameraSystem",
				"WorldUtilities",
				"LevelStreaming",
				"WorldPartition",
				"MovieSceneUtilities",
				"LevelSequenceSystem",
				"MediaSystem",
				"PropertyUtilities",

				/* Dev Lab */
				"PropertyDetailViewSystem",

				/* Marketplace */
				"DBTween", 
				"UltraDynamicSkyUtilities",
			}
		);
	}
}