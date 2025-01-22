using UnrealBuildTool;

public class GameHUDModule : ModuleRules
{
	public GameHUDModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"UMG",
				"GameplayTags",
				"DeveloperSettings",

				"DevCore",
				"DevSlateCore",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"WidgetGeneration"
			}
		);
	}
}