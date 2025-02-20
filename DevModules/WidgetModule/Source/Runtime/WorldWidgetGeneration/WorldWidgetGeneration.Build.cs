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
				"CommonUI",
				"GameplayTags",
				"DeveloperSettings",
				"InputCore",

				"WidgetGeneration",
				"GameHUDModule",
				"InteractableWidgetGeneration",
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