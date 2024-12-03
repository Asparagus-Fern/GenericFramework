using UnrealBuildTool;

public class UnrealEdGDAL : ModuleRules
{
	public UnrealEdGDAL(ReadOnlyTargetRules Target) : base(Target)
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

				"BlueprintGraph",

				"UnrealGDAL"
			}
		);
	}
}