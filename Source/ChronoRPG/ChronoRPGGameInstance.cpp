// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "ChronoRPGGameInstance.h"
#include "InteractionComponentBase.h"

void UChronoRPGGameInstance::PushNewInteractionCommand(UInteractionComponentBase* NewInteractionCommand)
{
	InteractionCommandStack.Add(NewInteractionCommand);
}

void UChronoRPGGameInstance::PopInteractionCommand(UInteractionComponentBase* InteractionCommandToRemove)
{
	if (InteractionCommandStack.Num() > 0)
	{
		InteractionCommandStack.RemoveSingle(InteractionCommandToRemove);
	}
}

UInteractionComponentBase* UChronoRPGGameInstance::GetLatestInteractionCommand()
{
	if (InteractionCommandStack.Num() > 0)
	{
		return InteractionCommandStack.Last();
	}
	else
	{
		return nullptr;
	}
}
