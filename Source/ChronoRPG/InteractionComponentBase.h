// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHRONORPG_API UInteractionComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponentBase();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ExecuteInteraction(class AChronoRPGCharacter* Instigator);

	UFUNCTION(BlueprintPure, Category = "Widget")
	FText GetInteractionText() const { return InteractionText; }

	UFUNCTION(BlueprintPure, Category = "Widget")
	FText GetAlternativeInteractionText() const { return AlternativeInteractionText; }


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// What is the main text this interaction component prompts the player with?
	// If not set in code, remember to set in Blueprint
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	FText InteractionText;
		
	// Secondary interaction text
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	FText AlternativeInteractionText;
};
