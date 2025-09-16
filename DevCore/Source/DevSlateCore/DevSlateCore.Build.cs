using UnrealBuildTool;

public class DevSlateCore : ModuleRules
{
	public DevSlateCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrecompileForTargets = PrecompileTargetsType.Any;
		bUsePrecompiled = false;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Projects",
				"UMG",
				"CommonUI",
				"GameplayTags"
			}
		);

		if (Target.bBuildEditor) PrivateDependencyModuleNames.Add("UnrealEd");
	}
}