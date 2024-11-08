using UnrealBuildTool;

public class MovieSceneUMGEdModule : ModuleRules
{
	public MovieSceneUMGEdModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"DevEdCore",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"UnrealEd",
				"UMG",
				"Sequencer",
				"MovieScene",
				"ContentBrowser",
				"ClassViewer",
				"UMGEditor",
				"MovieSceneTools",
				"MovieSceneTracks",

				"MovieSceneUMGModule"
			}
		);
	}
}