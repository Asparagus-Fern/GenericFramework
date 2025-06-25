using UnrealBuildTool;

public class DevGameplay : ModuleRules
{
	public DevGameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"PlayerInputUtilities",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"DeveloperSettings",
				"InputCore",
				"EnhancedInput",
				"AIModule",
				"GameplayCameras",

				"CameraSystem",
				"UnrealMisc"
			}
		);
	}
}