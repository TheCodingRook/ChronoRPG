// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "InteractablePropBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "InteractionComponentBase.h"

// Sets default values
AInteractablePropBase::AInteractablePropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PropMesh = CreateDefaultSubobject<UStaticMeshComponent>("Prop Mesh");
	//PropMesh->SetupAttachment(RootComponent);
	SetRootComponent(PropMesh);  // set it up as root component

	InteractionTrigger = CreateDefaultSubobject<USphereComponent>("Interaction Trigger");
	InteractionTrigger->SetSphereRadius(100.f);
	InteractionTrigger->SetupAttachment(PropMesh);

	// Set up a default value for the prop's name 
	PropName = FText::FromString("Unnamed");
}

void AInteractablePropBase::OnWasInteractedWith_Implementation()
{
	// To be extended in Blueprint
}

void AInteractablePropBase::OnReEnableInteraction_Implementation()
{
	// To be extended in Blueprint
}

// Called when the game starts or when spawned
void AInteractablePropBase::BeginPlay()
{
	Super::BeginPlay();

	// Set up the interaction component
	if (!InteractionClass)
	{
		UE_LOG(LogTemp, Error, TEXT("You have not specified an interaction component class for: %s"), *GetName())
	}
	else
	{
		InteractionCommand = NewObject<UInteractionComponentBase>(this, InteractionClass);
		if (InteractionCommand)
		{
			InteractionCommand->RegisterComponent();
		}
	}
	
}

// Called every frame
void AInteractablePropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

