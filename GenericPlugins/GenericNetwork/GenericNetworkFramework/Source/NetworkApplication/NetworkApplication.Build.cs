using UnrealBuildTool;

public class NetworkApplication : ModuleRules
{
	public NetworkApplication(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DevCore",
				"GenericGameplaySystem",
				"GenericNetworkFramework",
				"NetworkUserSystem",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				
				"OnlineSubsystem",
				"OnlineSubsystemUtils",
			}
		);
	}
}