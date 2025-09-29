using UnrealBuildTool;

public class WidgetGeneration : ModuleRules
{
	public WidgetGeneration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc",
				"DevCore",
				"DevSlateCore",

				"UMG",
				"GameplayTags",
				"CommonUI",
				"CommonInput",
				"InputCore"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				"ModelViewViewModel",
				"DeveloperSettings"
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
			PrivateDependencyModuleNames.Add("UMGEditor");
		}
	}
}