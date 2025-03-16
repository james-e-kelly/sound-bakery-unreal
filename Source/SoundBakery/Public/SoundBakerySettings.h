#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "SoundBakerySettings.generated.h"

UCLASS(Config=Engine, DefaultConfig, Category=Audio, meta = (DisplayName = "Sound Bakery", Tooltip = "Sound Bakery settings for integration and runtime"))
class SOUNDBAKERY_API USoundBakerySettings : public UDeveloperSettingsBackedByCVars
{
    GENERATED_BODY()

public:
    USoundBakerySettings();

    UPROPERTY(Config, EditDefaultsOnly, Category = Setup, meta = (RelativeToGameContentDir, Tooltip = "Directory to search for Soundbanks from the Sound Bakery project"))
    FDirectoryPath SoundbankDirectory;

    UPROPERTY(Config, EditDefaultsOnly, Category = Setup, meta = (RelativeToGameContentDir, Tooltip = "Directory to add Sound Bakery Unreal assets to. Should not be equal to the SoundbankDirectory"))
    FDirectoryPath ContentDirectory;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Debug", meta = (ConsoleVariable = "sbk.DisplayEmitters", Tooltip = "Whether to debug draw emitters in the world"))
    uint8 bDisplayEmitters : 1;
};
