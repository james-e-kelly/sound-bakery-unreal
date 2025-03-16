// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoundBakery.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "SoundBakeryLibrary/sound_bakery/sound_bakery.h"

#define LOCTEXT_NAMESPACE "FSoundBakeryModule"

void FSoundBakeryModule::StartupModule()
{
	const FString BaseDir = IPluginManager::Get().FindPlugin("SoundBakery")->GetBaseDir();
#if UE_BUILD_SHIPPING
	const FString ConfigFolder = "Release";
#else
	const FString ConfigFolder = "Debug";
#endif

	FString PlatformFolder;
	FString SoundBakeryLibraryPath;
	FString SoundChefLibraryPath;

#if PLATFORM_WINDOWS
	const FString LibraryFolder = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/SoundBakeryLibrary/x64"), ConfigFolder);
	SoundBakeryLibraryPath = FPaths::Combine(LibraryFolder, TEXT("sound_bakery_shared.dll"));
	SoundChefLibraryPath = FPaths::Combine(LibraryFolder, TEXT("sound_chef_shared.dll"));
#elif PLATFORM_MAC
	const FString LibraryFolder = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/SoundBakeryLibrary/Mac"), ConfigFolder);
	SoundBakeryLibraryPath = FPaths::Combine(LibraryFolder, TEXT("libsound_bakery_shared.dylib"));
	SoundChefLibraryPath = FPaths::Combine(LibraryFolder, TEXT("libsound_chef_shared.dylib"));
#elif PLATFORM_LINUX
	const FString LibraryFolder = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/SoundBakeryLibrary/Linux"), ConfigFolder);
	SoundBakeryLibraryPath = FPaths::Combine(LibraryFolder, TEXT("libsound_bakery_shared.so"));
	SoundChefLibraryPath = FPaths::Combine(LibraryFolder, TEXT("libsound_chef_shared.so"));
#endif

	// Load Sound Chef first as Sound Bakery depends on it
	SoundChefLibraryHandle = !SoundBakeryLibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*SoundChefLibraryPath) : nullptr;
	SoundBakeryLibraryHandle = !SoundBakeryLibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*SoundBakeryLibraryPath) : nullptr;

	if (SoundBakeryLibraryHandle && SoundChefLibraryHandle)
	{
		sb_system_config config = sb_system_config_init_default();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load Sound Bakery libraries"));
	}
}

void FSoundBakeryModule::ShutdownModule()
{
	FPlatformProcess::FreeDllHandle(SoundBakeryLibraryHandle);
	FPlatformProcess::FreeDllHandle(SoundChefLibraryHandle);
	SoundBakeryLibraryHandle = nullptr;
	SoundChefLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSoundBakeryModule, SoundBakery)
