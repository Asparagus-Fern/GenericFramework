using UnrealBuildTool;

public class ApplicationDeveloper : ModuleRules
{
	public ApplicationDeveloper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Blutility",
				"UnrealEd",
				"GraphEditor",
				"BlueprintGraph",
				"KismetCompiler"
			}
		);
	}
}