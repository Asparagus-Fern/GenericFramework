using UnrealBuildTool;

public class LevelSequenceSystem : ModuleRules
{
	public LevelSequenceSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
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

				"LevelSequence",
				"MovieScene",
			}
		);
	}
}