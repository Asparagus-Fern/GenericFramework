using UnrealBuildTool;

public class MovieSceneEdUtilities : ModuleRules
{
	public MovieSceneEdUtilities(ReadOnlyTargetRules Target) : base(Target)
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

				"DeveloperSettings",
				"EditorSubsystem",

				"UnrealEd",
				"UMG",
				"UMGEditor",

				"Sequencer",
				"MovieScene",
				"MovieSceneTools",
				"MovieSceneTracks",
				"LevelSequence",

				"ContentBrowser",
				"ClassViewer",

				"MovieSceneUtilities"
			}
		);
	}
}