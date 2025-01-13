// Copyright Epic Games, Inc. All Rights Reserved.

#include "UGCItemFrameworkGameMode.h"
#include "UGCItemFrameworkCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUGCItemFrameworkGameMode::AUGCItemFrameworkGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
