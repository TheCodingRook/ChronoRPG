// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimePortal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPortalTraversal);

/*
 * Simple base class to implement time portals in the game. Main responsibilities include
 * sending out an event dispatch to inform of a time-travel event, and resetting scene or 
 * world by moving objects and other actors in their positions in an earlier point in time
 */
UCLASS()
class CHRONORPG_API ATimePortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimePortal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Delegate to notify (anyone who's listening to this event) that character (or anyone else) has traversed through this Time Portal
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Event Dispatchers", meta = (AllowPrivateAccess = true))
	FOnPortalTraversal OnPortalTraversal;

protected:
	// Boolean to toggle the portal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = true))
	bool bIsActive = true;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Set up Components for the time portal in order to implement both the in-game functionality but also some additional
	// elements to help with setup and placement while working in the Editor
	//
	// Default root SceneComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	class USceneComponent* DefaultRoot;

	// Bounds for the portal that triggers time (and space) travel
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	class UBoxComponent* PortalTrigger;

	// Bounds for a "screen door" on the flip side to allow actors to go through
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	UBoxComponent* AllowThroughToggle;

	// Mesh to render the portal projector on
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* PortalScreen;

	// The teleport point/location that this portal is linked to (in 3D space, somewhere else in the level)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	USceneComponent* TeleportLocation;

	// A "helper" text render so we can see exactly where the teleport spawn point is while working in the Editor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	class UTextRenderComponent* TeleportLocationText;

	// An additional "helper" in the form of an arrow so we can see exactly where the telport spawn point is while working in the Editor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	class UArrowComponent* TeleportLocationArrow;

	// SceneCapture component that will display where the character will spawn to in space (and presumably the specific timeline...)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = true))
	class USceneCaptureComponent2D* PortalSceneCapture;
	//
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
