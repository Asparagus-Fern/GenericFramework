using System.IO;
using UnrealBuildTool;

public class gdal : ModuleRules
{
	public gdal(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

			// Delay-load the DLL, so we can load it from the right place first

			PublicDelayLoadDLLs.Add("gdal.dll");
			PublicDelayLoadDLLs.Add("geos_c.dll");
			PublicDelayLoadDLLs.Add("proj_9_2.dll");
			PublicDelayLoadDLLs.Add("geos.dll");
			PublicDelayLoadDLLs.Add("tiff.dll");
			PublicDelayLoadDLLs.Add("tiffxx.dll");

			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "gdal.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "geos_c.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "proj.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "geos.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "tiff.lib"));

			// Ensure that the DLL is staged along with the executable
			// RuntimeDependencies.Add("$(PluginDir)/Binaries/gdal/Win64/ExampleLibrary.dll");
			RuntimeDependencies.Add("$(PluginDir)/Source/gdal/bin/gdal.dll");

			RuntimeDependencies.Add("$(PluginDir)/Source/gdal/lib/geos_c.dll");
			RuntimeDependencies.Add("$(PluginDir)/Source/gdal/lib/proj_9_2.dll");
			RuntimeDependencies.Add("$(PluginDir)/Source/gdal/lib/geos.dll");
			RuntimeDependencies.Add("$(PluginDir)/Source/gdal/lib/tiff.dll");
			RuntimeDependencies.Add("$(PluginDir)/Source/gdal/lib/tiffxx.dll");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
			RuntimeDependencies.Add("$(PluginDir)/Source/gdal/Mac/Release/libExampleLibrary.dylib");
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string ExampleSoPath = Path.Combine("$(PluginDir)", "Binaries", "ThirdParty", "gdal", "Linux", "x86_64-unknown-linux-gnu", "libExampleLibrary.so");
			PublicAdditionalLibraries.Add(ExampleSoPath);
			PublicDelayLoadDLLs.Add(ExampleSoPath);
			RuntimeDependencies.Add(ExampleSoPath);
		}
	}
}