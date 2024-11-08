using UnrealBuildTool;

public class MovieSceneUMGModule : ModuleRules
{
	public MovieSceneUMGModule(ReadOnlyTargetRules Target) : base(Target)
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
				
				"UMG",
				"MovieScene",
				"MovieSceneTracks",
				"LevelSequence"
			}
		);
	}
}