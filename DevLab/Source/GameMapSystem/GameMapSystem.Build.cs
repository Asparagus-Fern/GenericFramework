using UnrealBuildTool;

public class GameMapSystem : ModuleRules
{
	public GameMapSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
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
				
				"UMG",
				"CommonUI",
				"DeveloperSettings",

				"WidgetGeneration",
			}
		);
	}
}