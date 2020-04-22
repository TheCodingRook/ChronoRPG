// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractablePropBase.generated.h"

/*
 * Base class to implement actor props (objects) that the player can interact with in the world
*/

UCLASS()
class CHRONORPG_API AInteractablePropBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractablePropBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Mesh")
	UStaticMeshComponent* GetMesh() const { return PropMesh; }

	UFUNCTION(BlueprintPure, Category = "Interaction Trigger")
	USphereComponent* GetInteractionTrigger() const { return InteractionTrigger; }

	UFUNCTION(BlueprintPure, Category = "Widget")
	FText GetPropName() const { return PropName; }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	class UInteractionComponentBase* GetInteractionCommand() const { return InteractionCommand; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnWasInteractedWith();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnReEnableInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PropMesh;

	UPROPERTY(VisibleAnywhere, Category = "Interaction Trigger", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* InteractionTrigger;

	// Name this prop for the interaction and text prompt
	UPROPERTY(EditDefaultsOnly, Category = "Widget Setup", meta = (AllowPrivateAccess = "true"))
	FText PropName;

	// Class that implements the interaction for this prop
	UPROPERTY(EditDefaultsOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInteractionComponentBase> InteractionClass;

	// Interaction command for this prop
	UPROPERTY(VisibleAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	UInteractionComponentBase* InteractionCommand;
};
