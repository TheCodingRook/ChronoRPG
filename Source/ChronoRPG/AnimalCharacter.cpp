// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "AnimalCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AAnimalCharacter::AAnimalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a collision sphere to serve as a mouth socket (for detecting eating/biting)
	MouthCollision = CreateDefaultSubobject<USphereComponent>("Mouth Collision");
	MouthCollision->SetupAttachment(GetMesh(), "MouthSocket");

}

// Called when the game starts or when spawned
void AAnimalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
