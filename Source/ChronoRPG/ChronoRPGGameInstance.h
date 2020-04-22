// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ChronoRPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHRONORPG_API UChronoRPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	void PushNewInteractionCommand(class UInteractionComponentBase* NewInteraction);

	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	void PopInteractionCommand(UInteractionComponentBase* InteractionCommandToRemove);

	UFUNCTION(BlueprintCallable, Category = "Interaction Commands")
	UInteractionComponentBase* GetLatestInteractionCommand();

	UFUNCTION(BlueprintPure, Category = "Interaction Commands")
	TArray<UInteractionComponentBase*> GetInteractionCommandStack() const {return InteractionCommandStack; }

private:
	TArray<UInteractionComponentBase*> InteractionCommandStack;
};
