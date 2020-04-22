// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "InteractionComponentBase.h"
#include "InteractablePropBase.h"

// Sets default values for this component's properties
UInteractionComponentBase::UInteractionComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	InteractionText = FText::FromString("Interact with").ToUpper();
}

// Called every frame
void UInteractionComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponentBase::ExecuteInteraction(AChronoRPGCharacter* Instigator)
{
	if (AInteractablePropBase* OwnerProp = Cast<AInteractablePropBase>(GetOwner()))
	{
		OwnerProp->OnWasInteractedWith();
	}
}

// Called when the game starts
void UInteractionComponentBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




