using UnrealBuildTool;

public class MovieSceneUtilities : ModuleRules
{
	public MovieSceneUtilities(ReadOnlyTargetRules Target) : base(Target)
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
				"CommonUI",
				"MovieScene",
				"LevelSequence",

				"EventUtilities",
				"WidgetGeneration",
			}
		);
	}
}