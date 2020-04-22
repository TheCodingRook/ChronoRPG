// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ChronoRPGGameMode.h"
#include "ChronoRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AChronoRPGGameMode::AChronoRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/Blueprints/BP_ChronoRPGCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
