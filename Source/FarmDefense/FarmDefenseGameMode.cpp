// Copyright Epic Games, Inc. All Rights Reserved.

#include "FarmDefenseGameMode.h"
#include "FarmDefenseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFarmDefenseGameMode::AFarmDefenseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
