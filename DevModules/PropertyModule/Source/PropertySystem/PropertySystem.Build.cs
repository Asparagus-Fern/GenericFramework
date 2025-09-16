using UnrealBuildTool;

public class PropertySystem : ModuleRules
{
	public PropertySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"DevSlateCore",
				"UnrealMisc"
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
				"ModelViewViewModel",
				"PropertyPath",
				"GameplayTags",

				"WidgetGeneration",
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}