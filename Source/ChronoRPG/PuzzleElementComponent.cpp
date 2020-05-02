// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "PuzzleElementComponent.h"

// Sets default values for this component's properties
UPuzzleElementComponent::UPuzzleElementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPuzzleElementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPuzzleElementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPuzzleElementComponent::SetElementTriggeredFlag(bool InFlag)
{
	bIsTriggered = InFlag;
}

void UPuzzleElementComponent::SetPuzzleElementType(EPuzzleElementType InElementType)
{
	PuzzleElementType = InElementType;
}