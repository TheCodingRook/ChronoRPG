// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActivateTriggerPlatform.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UActivateTriggerPlatform : public UInterface
{
	GENERATED_BODY()
};

/**
 * Custom interface class to implement activation of platform triggers. Actors that implemnt it will be able to
 * activate the platform once placed on it.
 */
class CHRONORPG_API IActivateTriggerPlatform
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Trigger Reaction")
	void OnStandingOnPlatform(); //TODO CODINGROOK: DO I NEED THIS?
};
