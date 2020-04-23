// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponentBase.h"
#include "GrabInteraction.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = Custom, meta = (BlueprintSpawnableComponent))
class CHRONORPG_API UGrabInteraction : public UInteractionComponentBase
{
	GENERATED_BODY()

protected:
	UGrabInteraction();

	virtual void ExecuteInteraction(AChronoRPGCharacter* Instigator) override;
	
};
