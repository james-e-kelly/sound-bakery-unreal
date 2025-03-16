#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "SoundBakerySettings.generated.h"

UCLASS(Config=Game, DefaultConfig, Category=Audio)
class MYGAME_API USoundBakerySettings : public UDeveloperSettingsBackedByCVars
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditDefaultsOnly, Category = Setup, meta = (RelativeToGameContentDir))
    FDirectoryPath BankOutputDirectory;

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Graphics", meta = (ConsoleVariable = "sbk.DisplayEmitters"))
    int32 DisplayEmitters;
};
