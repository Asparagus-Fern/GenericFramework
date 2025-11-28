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
				"UMG",
				"GameplayTags",
				"CommonUI",
				"CommonInput",
				"InputCore",
				"ModelViewViewModel",
				
				"UnrealMisc",
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
				"DeveloperSettings",
				"MoviePlayer"
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
			PrivateDependencyModuleNames.Add("UMGEditor");
		}
	}
}