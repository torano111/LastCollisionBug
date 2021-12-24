// Copyright Epic Games, Inc. All Rights Reserved.

#include "LastCollisionBugGameMode.h"
#include "LastCollisionBugCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALastCollisionBugGameMode::ALastCollisionBugGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
