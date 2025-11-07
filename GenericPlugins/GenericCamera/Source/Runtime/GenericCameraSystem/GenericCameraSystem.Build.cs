using UnrealBuildTool;

public class GenericCameraSystem : ModuleRules
{
	public GenericCameraSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"UnrealMisc",
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
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("DevEdCore");
			PrivateDependencyModuleNames.Add("UnrealEd");
			PrivateDependencyModuleNames.Add("LevelEditor");
		}
	}
}