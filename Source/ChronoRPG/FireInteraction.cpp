// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "FireInteraction.h"

UFireInteraction::UFireInteraction()
{
	InteractionText = FText::FromString("Light").ToUpper();
}

void UFireInteraction::ExecuteInteraction(AChronoRPGCharacter* Instigator)
{
	LightFire(Instigator);
}
