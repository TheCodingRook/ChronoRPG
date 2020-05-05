// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "PuzzleVisComponent.h"
#include "PuzzleComponent.h"
#include "PuzzleElementComponent.h"
#if !UE_BUILD_SHIPPING
#include "DrawDebugHelpers.h"
#endif

// Sets default values for this component's properties
UPuzzleVisComponent::UPuzzleVisComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = PrimaryComponentTick.bStartWithTickEnabled = true;
	bTickInEditor = true;

	// ...
}


void UPuzzleVisComponent::PostLoad()
{
	Super::PostLoad();
}

void UPuzzleVisComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

// Called when the game starts
void UPuzzleVisComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

#if WITH_EDITORONLY_DATA
void UPuzzleVisComponent::ToggleSpheres()
{
	bShowSpheres = !bShowSpheres;
}
#endif //WITH_EDITORONLY_DATA

// Called every frame
void UPuzzleVisComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TickType == ELevelTick::LEVELTICK_ViewportsOnly)
	{
		AActor* OwnerActor = GetOwner();
		
		// Get the Puzzle component via the array returned by GetCompnents()
		TInlineComponentArray<UPuzzleComponent*> GrabComponents;
		OwnerActor->GetComponents(GrabComponents);

		// We expect this to be the first and only component of its kind!
		UPuzzleComponent* Puzzle = GrabComponents.Top();

		if (bKeepDebugDisplayOn || IsOwnerSelected())
		{
			if (UWorld* World = GetWorld())
			{
				const FVector BaseLocation = GetComponentLocation();
				for (AActor* PuzzleElementActor : Puzzle->GetActorsList())
				{
					if (PuzzleElementActor)
					{
						FVector Origin;
						FVector Extents;
						PuzzleElementActor->GetActorBounds(true, Origin, Extents);

						const float Radius = Extents.Size();
						const FVector Direction = (Origin - BaseLocation).GetSafeNormal();

						if (bShowSpheres && (Radius < (Origin - BaseLocation).Size()))
						{
							DrawDebugDirectionalArrow(World, BaseLocation, Origin - (Direction * Radius), 40.0f, FColor::Red, false, 0.001f, 255, 2.0f);
							DrawDebugSphere(World, Origin, Radius, 16, FColor::Red, false, 0.001f, 255, 1.0f);
						}
						else
						{
							DrawDebugDirectionalArrow(World, BaseLocation, Origin, 40.0f, FColor::Red, false, 0.001f, 255, 2.0f);
						}
					}
				}
			}
		}
		
	}
}

