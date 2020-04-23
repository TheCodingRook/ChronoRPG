// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "GrabbingAbility.h"
#include "ChronoRPGCharacter.h"
#include "InteractablePropBase.h"

void UGrabbingAbility::GrabProp(AActor* In_AActor)
{
	OwnerCharacter = Cast<AChronoRPGCharacter>(GetOwner());

	if (AInteractablePropBase* PropToGrab = Cast<AInteractablePropBase>(In_AActor))
	{
		// First check to see that we are not already holding on to something else
		if (bIsAlreadyHoldingSomething)
		{
			// Are we holding the same thing we are trying to grab?
			if (PropToGrab == PropAlreadyHeld)
			{
				return; // If so, do nothing and return
			}
			else
			{
				// We are holding something different, so drop that and will pick up new prop
				DropProp();
			}
		}

		// Save the pawn channel's collision resposnse setting before setting to "Ignore"
		OriginalPawnECR = PropToGrab->GetMesh()->GetCollisionResponseToChannel(ECC_Pawn);
		PropToGrab->GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

		// Pick up the prop, whether by phyics handle or attaching to a socket
		if (PropToGrab->ActorHasTag(AttachableTag))
		{
			// This prop can be attached to a socket, but first stop simulating physics
			PropToGrab->GetMesh()->SetSimulatePhysics(false);
			PropToGrab->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "GrabSocket");
		}
		else
		{
			// We can alternatively pick this prop up using the default physics handle component
			GrabComponentAtLocation(PropToGrab->GetMesh(), NAME_None, PropToGrab->GetMesh()->GetCenterOfMass());
		}

		// We are now grabbing/holding something, so set the necessary member fields
		bIsAlreadyHoldingSomething = true;
		PropAlreadyHeld = PropToGrab;
	}
}

void UGrabbingAbility::DropProp()
{
	// First check if we are using the physics handle; if so, the pointer GrabbedComponent will be non-null
	if (GrabbedComponent)
	{
		// Reset the collision channel for pawns back to original setting
		GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, OriginalPawnECR);
		ReleaseComponent();
	}
	// Otherwise let's see if we have a prop that we are grabbing (the PropAlreadyHeld is non-null)
	else if(PropAlreadyHeld)
	{
		// Detach from socket and re-enable physics
		PropAlreadyHeld->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		PropAlreadyHeld->GetMesh()->SetSimulatePhysics(true);
		PropAlreadyHeld->GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, OriginalPawnECR);
	}
	else
	{
		return; // We are not holding anything; do nothing and return
	}

	// Reset the necessary member fields
	bIsAlreadyHoldingSomething = false;
	PropAlreadyHeld->OnReEnableInteraction();
	PropAlreadyHeld = nullptr;
}

void UGrabbingAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GrabbedComponent)
	{
		// If this prop was grabbed using the physics handle functionality...
		if (!GrabbedComponent->GetOwner()->ActorHasTag(AttachableTag))
		{
			// ... update its location every tick to be in front of the character
			SetTargetLocation(OwnerCharacter->ActorToWorld().GetLocation() + OwnerCharacter->GetActorForwardVector() * GrabDistance);
		}
	}

}