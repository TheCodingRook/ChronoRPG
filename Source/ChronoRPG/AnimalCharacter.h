// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalCharacter.generated.h"

/*
 * Custom class to implement animal characters in ChronoRPG 
 */

UCLASS()
class CHRONORPG_API AAnimalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimalCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Differentiate between a walking max speed and running/galloping max speed
	// Max walk speed will initially be driven by CharacterMovementComponent's setting
	UFUNCTION(BlueprintPure, Category = "Animal Movement")
	float GetMaxAnimalWalkSpeed() const { return MaxAnimalWalkSpeed; }
	UFUNCTION(BlueprintPure, Category = "Animal Movement")
	float GetMaxAnimalRunSpeed() const { return MaxAnimalRunSpeed; }
	UFUNCTION(BlueprintPure, Category = "Animal Behavior")
	float GetMinSafetyDistance() const { return MinSafetyDistance; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animal Movement")
	float MaxAnimalWalkSpeed;	// This is set by CharacterMovementComponent's setting initially
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animal Movement")
	float MaxAnimalRunSpeed; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animal Movement")
	float MinSafetyDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animal Behavior", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* MouthCollision;
};
