// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponentBase.h"
#include "FireInteraction.generated.h"

/**
 * Simple base class for the Fire Interaction command (to light torches, braziers and other fires in general)
 */
UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class CHRONORPG_API UFireInteraction : public UInteractionComponentBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction")
	void LightFire(AChronoRPGCharacter* Instigator);

protected:
	UFireInteraction();
	virtual void ExecuteInteraction(AChronoRPGCharacter* Instigator) override;
};
