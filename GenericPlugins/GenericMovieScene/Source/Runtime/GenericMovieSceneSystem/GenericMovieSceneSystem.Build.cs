using UnrealBuildTool;

public class GenericMovieSceneSystem : ModuleRules
{
	public GenericMovieSceneSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"WidgetGeneration"
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