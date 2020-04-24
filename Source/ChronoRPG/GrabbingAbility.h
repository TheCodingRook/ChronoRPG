// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabbingAbility.generated.h"

/**
 * Custom PhysicsHandleComponent to implement grabbing props functionality 
 */
UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class CHRONORPG_API UGrabbingAbility : public UPhysicsHandleComponent
{
	GENERATED_BODY()

public:
	//~ Getter methods

	UFUNCTION(BlueprintPure, Category = "Grab Configuration")
	float GetGrabDistance() const { return GrabDistance; }

	UFUNCTION(BlueprintCallable, Category = "Grab Configuration")
	void GrabProp(AActor* In_AActor);

	UFUNCTION(BlueprintCallable, Category = "Grab Configuration")
	void DropProp();

	UFUNCTION(BlueprintPure, Category = "Grab Configuration")
	bool IsAlreadyHoldingSomething() const { return bIsAlreadyHoldingSomething; }

	UFUNCTION(BlueprintPure, Category = "Grab Configuration")
	FName GetAttachableTag() const { return AttachableTag; }

protected:
	//~ Set up some space and distance parameters for the grabbing ability (Remember it is IN CENTIMETERS!)

	// Minimum distance before the player can grab an object
	UPROPERTY(EditAnywhere, Category = "Grab Configuration")
	float GrabDistance = 100.f;

	// Radius of grabbing range when facing forward
	UPROPERTY(EditAnywhere, Category = "Grab Configuration")
	float GrabRadius = 50.f;

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick Ticktype, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Private member to store the pointer to the player character
	class AChronoRPGCharacter* OwnerCharacter;

	// Tag to indicate this prop can actually be held in hand (i.e. attached to a socket in hand, like a tool or weapon etc.)
	// Otherwise will use physicshandle functionality for other stuff for the time being (until correct animations come in!)
	const FName AttachableTag = "Attachable";

	// Store the pointer to the prop we are already holding at the moment
	class AInteractablePropBase* PropAlreadyHeld;

	// Are we holding something already?
	bool bIsAlreadyHoldingSomething = false;

	// Use this variable to store the grabbed mesh's original collision settings for the pawn channel
	ECollisionResponse OriginalPawnECR;
};
