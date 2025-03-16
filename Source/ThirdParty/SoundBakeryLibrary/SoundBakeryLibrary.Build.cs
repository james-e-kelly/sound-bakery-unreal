// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class SoundBakeryLibrary : ModuleRules
{
	public SoundBakeryLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		PublicSystemIncludePaths.Add("$(ModuleDir)/Public");
		PublicSystemIncludePaths.Add("$(ModuleDir)/Public/sound_bakery");
		PublicSystemIncludePaths.Add("$(ModuleDir)/Public/sound_chef");

		string RootFolder = ModuleDirectory;
		string PlatformFolder = string.Empty;
		string ConfigFolder = string.Empty;

        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            ConfigFolder = "Debug";
        }
		else
		{
			ConfigFolder = "Release";
		}

        const string SoundBakeryLibraryName = "sound_bakery_shared";
		const string SoundChefLibraryName = "sound_chef_shared";

		string LibraryPrefix = string.Empty;
		string LibraryExtension = string.Empty;
		string LibraryAdditionalExtension = string.Empty;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PlatformFolder = "x64";
			LibraryExtension = ".dll";
			LibraryAdditionalExtension = ".lib";

        }
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
            PlatformFolder = "Mac";
            LibraryExtension = ".dylib";
			LibraryPrefix = "lib";
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
            PlatformFolder = "Linux";
            LibraryExtension = ".so";
			LibraryPrefix = "lib";
		}

		string PluginFolder = Path.Combine(RootFolder, PlatformFolder, ConfigFolder);

		string SoundBakeryLibraryNameFull = LibraryPrefix + SoundBakeryLibraryName + LibraryExtension;
		string SoundBakeryAdditionalLibraryNameFull = LibraryPrefix + SoundBakeryLibraryName + LibraryAdditionalExtension;
		string SoundChefLibraryNameFull = LibraryPrefix + SoundChefLibraryName + LibraryExtension;
		string SoundChefAdditionalLibraryNameFull = LibraryPrefix + SoundChefLibraryName + LibraryAdditionalExtension;

		string SoundBakeryLibraryFile = Path.Combine(PluginFolder, SoundBakeryLibraryNameFull);
		string SoundBakeryAdditionalLibraryFile = LibraryAdditionalExtension.Length > 0 ? Path.Combine(PluginFolder, SoundBakeryAdditionalLibraryNameFull) : string.Empty;
        string SoundChefLibraryFile = Path.Combine(PluginFolder, SoundChefLibraryNameFull);
        string SoundChefAdditionalLibraryFile = LibraryAdditionalExtension.Length > 0 ? Path.Combine(PluginFolder, SoundChefAdditionalLibraryNameFull) : string.Empty;

		if (SoundBakeryAdditionalLibraryFile.Length > 0)
		{
			PublicAdditionalLibraries.Add(SoundBakeryAdditionalLibraryFile);
		}

		if (SoundChefAdditionalLibraryFile.Length > 0)
		{
			PublicAdditionalLibraries.Add(SoundChefAdditionalLibraryFile);
		}

        PublicDelayLoadDLLs.Add(SoundBakeryLibraryNameFull);
        PublicDelayLoadDLLs.Add(SoundChefLibraryNameFull);

        RuntimeDependencies.Add("${TargetOutputDir}/" + SoundBakeryLibraryNameFull, SoundBakeryLibraryFile);
        RuntimeDependencies.Add("${TargetOutputDir}/" + SoundChefLibraryNameFull, SoundBakeryLibraryFile);
    }
}
