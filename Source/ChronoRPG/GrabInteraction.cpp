// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "GrabInteraction.h"
#include "ChronoRPGCharacter.h"
#include "InteractablePropBase.h"
#include "GrabbingAbility.h"

UGrabInteraction::UGrabInteraction()
{
	InteractionText = FText::FromString("Grab").ToUpper();
	AlternativeInteractionText = FText::FromString("Swap to").ToUpper();
}

void UGrabInteraction::ExecuteInteraction(AChronoRPGCharacter* Instigator)
{
	Super::ExecuteInteraction(Instigator);

	AInteractablePropBase* PropToGrab = Cast<AInteractablePropBase>(GetOwner());

	// Get the Grabbing ability component via the array returned by GetCompnents()
	TInlineComponentArray<UGrabbingAbility*> GrabComponents;
	Instigator->GetComponents(GrabComponents);

	// We expect this to be the first and only component of its kind!
	GrabComponents.Top()->GrabProp(PropToGrab);
}
