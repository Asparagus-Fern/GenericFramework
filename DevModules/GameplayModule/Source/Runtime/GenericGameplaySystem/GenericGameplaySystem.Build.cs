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
				"UnrealMisc",
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

				"DeveloperSettings",
				"InputCore",
				"EnhancedInput",
				"AIModule",
				"GameplayCameras",
				"PlayerInputUtilities",

				"CameraSystem",
				"WidgetGeneration"
			}
		);
	}
}