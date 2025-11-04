using UnrealBuildTool;

public class GenericProtocol : ModuleRules
{
	public GenericProtocol(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealMisc",
				"DevCore",
				"GenericJson",
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
				"HTTP",
				"HTTPServer",
				"Sockets",
				"WebSockets",
				"Networking",
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}