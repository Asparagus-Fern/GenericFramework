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

				"GameplayTags",
				"DBTween",
				"UMG",

				"ActiveNodeSystem",
				"ScreenWidgetGeneration",
				"WorldWidgetGeneration",
				"CameraSystem",
				"LevelStreaming",
				"WorldPartition",
				"PropertyDetailViewSystem",
			}
		);
	}
}