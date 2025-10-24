using UnrealBuildTool;

public class WidgetGroupGeneration : ModuleRules
{
	public WidgetGroupGeneration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc",
				"DevCore",
				"DevSlateCore",

				"InputCore",
				"EnhancedInput",
				"GameplayTags",
				"UMG",
				"ModelViewViewModel",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"WidgetGeneration",
			}
		);

		if (Target.bBuildEditor) PrivateDependencyModuleNames.Add("UnrealEd");
	}
}