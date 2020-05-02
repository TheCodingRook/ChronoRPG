// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponentBase.h"
#include "UnlockInteraction.generated.h"

/**
 * Custom component class to implement unlocking functionality for props that have a key/lock relationship
 */
UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class CHRONORPG_API UUnlockInteraction : public UInteractionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void UnlockProp(AChronoRPGCharacter* Instigator);

protected:
	UUnlockInteraction();
	virtual void ExecuteInteraction(AChronoRPGCharacter* Instigator) override;
};
