using UnrealBuildTool;

public class WidgetGroupGeneration : ModuleRules
{
	public WidgetGroupGeneration(ReadOnlyTargetRules Target) : base(Target)
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
				"GameplayTags",
				"CommonUI",
				"CommonInput",
				"InputCore",
				"EnhancedInput",
				
				"UnrealMisc",
				"WidgetGeneration",
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}