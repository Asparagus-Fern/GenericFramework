using UnrealBuildTool;

public class CameraSystem : ModuleRules
{
	public CameraSystem(ReadOnlyTargetRules Target) : base(Target)
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
				"CinematicCamera",
				"DeveloperSettings",

				"WidgetGeneration"
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("DevEdCore");
		}
	}
}