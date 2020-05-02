// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleElementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleElementTriggered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleElementUnTriggered);

UENUM(BlueprintType)
enum class EPuzzleElementType : uint8
{
	NOSwitch UMETA(DisplayName = "Normally Open Switch"),
	Toggle UMETA(DisplayName = "Toggle Switch"),
	Type_None UMETA(DisplayName = "Null type")
};

/*
 * A generic base component class to implement actors as "puzzle elements" that trigger events or solve other puzzles in combination with 
 * other actors that include the same component. The idea is that all actors that are linked through this component have to be activated together
 * (return true) in order for a puzzle to be solved.
 */
UCLASS(CollapseCategories, ClassGroup = Custom, Blueprintable, meta = (BlueprintSpawnableComponent))
class CHRONORPG_API UPuzzleElementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleElementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetElementTriggeredFlag(bool InFlag);

	// Delegate to nofity the Actor which this component's actor is linked with, that this PuzzleElement was triggered
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnPuzzleElementTriggered OnPuzzleElementTriggered;

	// Delegate to nofity the Actor which this component's actor is linked with, that this PuzzleElement was triggered as off or false or closed etc.
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnPuzzleElementUnTriggered OnPuzzleElementUnTriggered;

	UFUNCTION(BlueprintPure, Category = "Trigger")
	bool IsTriggered() const { return bIsTriggered; }

	// Set the puzzle element type (maybe best set by a constructor?) 
	UFUNCTION(BlueprintCallable, Category = "Puzzle Type")
	void SetPuzzleElementType(EPuzzleElementType InElementType);

	UFUNCTION(BlueprintPure, Category = "Puzzle Type")
	EPuzzleElementType GetPuzzleElementType() const { return PuzzleElementType; }


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// The main boolean member field that determines if this PuzzleElement is activated or not
	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	bool bIsTriggered;

	// The type of puzzle element this is (as per the above enumeration class
	EPuzzleElementType PuzzleElementType;
		
};
