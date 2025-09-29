using UnrealBuildTool;

public class MovieSceneExtend : ModuleRules
{
	public MovieSceneExtend(ReadOnlyTargetRules Target) : base(Target)
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
				"LevelSequence",
			}
		);

		if (Target.bBuildEditor)
		{
			PublicDependencyModuleNames.Add("DevEdCore");

			PrivateDependencyModuleNames.Add("UnrealEd");
			PrivateDependencyModuleNames.Add("EditorSubsystem");
			PrivateDependencyModuleNames.Add("UMGEditor");
			PrivateDependencyModuleNames.Add("ContentBrowser");
			PrivateDependencyModuleNames.Add("ClassViewer");
			PrivateDependencyModuleNames.Add("Sequencer");
			PrivateDependencyModuleNames.Add("MovieSceneTools");
			PrivateDependencyModuleNames.Add("MovieSceneTracks");
		}
	}
}