using UnrealBuildTool;

public class WorldWidgetGeneration : ModuleRules
{
	public WorldWidgetGeneration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc",
				"DevCore",
				"WidgetGeneration",
				"WidgetGroupGeneration",
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
				"GameplayTags",
				"CommonUI",
				"InputCore",
				"DeveloperSettings",
			}
		);

		if (Target.bBuildEditor)
		{
			PublicDependencyModuleNames.Add("DevEdCore");
			PrivateDependencyModuleNames.Add("LevelEditor");
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}