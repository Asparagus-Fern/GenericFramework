using UnrealBuildTool;

public class GenericMovieSceneEdSystem : ModuleRules
{
	public GenericMovieSceneEdSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"DevEdCore",
				"GenericMovieSceneSystem"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
				"MovieScene",
				"LevelSequence",
				"UnrealEd",
				"EditorSubsystem",
				"UMGEditor",
				"ContentBrowser",
				"ClassViewer",
				"Sequencer",
				"MovieSceneTools",
				"MovieSceneTracks",
			}
		);
	}
}