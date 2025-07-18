using UnrealBuildTool;

public class GenericGameplaySystem : ModuleRules
{
	public GenericGameplaySystem(ReadOnlyTargetRules Target) : base(Target)
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