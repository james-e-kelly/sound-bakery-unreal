#include "SoundBakerySettings.h"

namespace SoundBakerySettingsCVars
{
	static bool bDisplayEmitters = false;
	static FAutoConsoleVariableRef CVarDisplayEmitters(
		TEXT("sbk.DisplayEmitters"),
		bDisplayEmitters,
		TEXT("Whether to debug draw the active emitters in the world"),
		ECVF_Cheat);
}