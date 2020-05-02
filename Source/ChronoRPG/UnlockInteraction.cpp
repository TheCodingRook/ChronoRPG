// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "UnlockInteraction.h"

UUnlockInteraction::UUnlockInteraction()
{
	InteractionText = FText::FromString("Unlock").ToUpper();
}

void UUnlockInteraction::ExecuteInteraction(AChronoRPGCharacter* Instigator)
{
	// Not calling Super here because if unlock interaction is unavailable (e.g. due to lack of a corresponding key)
	// there is no point executing it (for now)
	// Super::ExecuteInteraction(Instigator);
	UnlockProp(Instigator);
}



