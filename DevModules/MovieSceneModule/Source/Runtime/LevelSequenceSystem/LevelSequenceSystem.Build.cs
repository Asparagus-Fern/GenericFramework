using UnrealBuildTool;

public class LevelSequenceSystem : ModuleRules
{
	public LevelSequenceSystem(ReadOnlyTargetRules Target) : base(Target)
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

				"LevelSequence",
				"MovieScene",

				"MovieSceneUtilities"
			}
		);
	}
}