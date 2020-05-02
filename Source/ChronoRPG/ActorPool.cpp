// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UActorPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UActorPool::CheckOut()
{
	if (Pool.Num() == 0)
	{
		return nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s CheckOut."), *GetName())
		return Pool.Pop();
}

void UActorPool::CheckIn(AActor* ActorToCheckIn)
{
	// Protect against null pointer
	if (ActorToCheckIn == nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("%s: Checked in NULL actor!"), *GetName())
		return;
	}

	Pool.Push(ActorToCheckIn);
	//UE_LOG(LogTemp, Warning, TEXT("%s: Checked in actor %s"), *GetName(), *ActorToCheckIn->GetName())
}

/*
void UActorPool::Add(AActor* ActorToAdd)
{
	// Protect against null pointer
	if (ActorToCheckIn == nulltpr)
	{
		UE_LOG(LogTemp, Error, Text("%s: Added NULL actor!"), *GetName())
		return;
	}

	Pool.Push(ActorToCheckIn);
	UE_LOG(LogTemp, Warning, TEXT("%s: Added actor %s"), *GetName(), *ActorToAdd->GetName())

}
*/

// Called when the game starts
void UActorPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




