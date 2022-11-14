// Copyright Epic Games, Inc. All Rights Reserved.

#include "PROJECT_TACTICALGameMode.h"
#include "PROJECT_TACTICALCharacter.h"
#include "UObject/ConstructorHelpers.h"

APROJECT_TACTICALGameMode::APROJECT_TACTICALGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
