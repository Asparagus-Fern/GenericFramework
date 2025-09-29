using UnrealBuildTool;
using System.IO;

public class UEAzSpeech : ModuleRules
{
	public UEAzSpeech(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;
		bEnableExceptions = true;

		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"AzureWrapper",
			"AzSpeech"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Engine",
			"CoreUObject",
			"Projects",
			"AndroidPermission",
			"DeveloperSettings",
			"AudioCaptureCore",
			"AssetRegistry",
			"Projects",
			"Json"
		});

		if (Target.bBuildEditor) PrivateDependencyModuleNames.Add("UnrealEd");

		PrivateIncludePathModuleNames.Add("DesktopPlatform");

		RuntimeDependencies.Add("$(PluginDir)/Resources/...*table", StagedFileType.NonUFS);
	}
}