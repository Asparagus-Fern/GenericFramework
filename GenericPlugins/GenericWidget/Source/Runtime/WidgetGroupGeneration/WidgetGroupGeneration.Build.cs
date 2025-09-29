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
				"DevSlateCore"
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
				"ModelViewViewModel",

				"WidgetGeneration"
			}
		);

		if (Target.bBuildEditor) PrivateDependencyModuleNames.Add("UnrealEd");
	}
}