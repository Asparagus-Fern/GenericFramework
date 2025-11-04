using UnrealBuildTool;

public class GenericGameplaySystem : ModuleRules
{
	public GenericGameplaySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc",
				"DevCore",
				"GenericCameraSystem",
				"WidgetGeneration",
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
				"GenericInputSystem",
			}
		);
	}
}