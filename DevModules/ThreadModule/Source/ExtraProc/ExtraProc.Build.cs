using UnrealBuildTool;

public class ExtraProc : ModuleRules
{
	public ExtraProc(ReadOnlyTargetRules Target) : base(Target)
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
				"DeveloperSettings",
				"UnrealMisc",
				"GenericThreadSystem"
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}

		RuntimeDependencies.Add("$(ProjectDir)/Extras/...", StagedFileType.NonUFS);
	}
}