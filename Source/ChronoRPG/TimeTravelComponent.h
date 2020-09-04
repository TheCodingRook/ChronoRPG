// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimeTravelComponent.generated.h"

// Struct representing a recorded action and its associated value
USTRUCT(BlueprintType)
struct FRecordedActionInput
{
	GENERATED_USTRUCT_BODY()

	// Default constructor
	FRecordedActionInput();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Struct Contents")
	FName RecordedAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Struct Contents")
	float InputValue;

};

// Struct to store unique timestamp entries with associated list of recorded actions
USTRUCT(BlueprintType)
struct FTimestampedActions
{
	GENERATED_USTRUCT_BODY()

	// Default constructor
	FTimestampedActions();

	// Constructor witha known timestamp (float value)
	FTimestampedActions(float NewTimeStamp);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Struct Contents")
	float TimeStamp = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Struct Contents")
	TArray<FRecordedActionInput> RecordedActionInputArray;
};

/* A custom class that allows the pawn to store its controller's input so it can be
 * replayed at a later time. Intended to be used to simulate a player travelling back
 * in time and encountering their "past self"
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHRONORPG_API UTimeTravelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeTravelComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	///////////////////////////////
	/* ~ Public getter functions */
	UFUNCTION(BlueprintPure, Category = "Time Travel")
	TArray<FTimestampedActions> GetTimestampedInputsArray() const { return TimestampedInputsArray; }

	UFUNCTION(BlueprintPure, Category = "Time Travel")
	float GetMaxRecordingTime() const { return MaxRecordingTime; }

	UFUNCTION(BlueprintPure, Category = "Time Travel")
	int GetMaxStructArraySize() const { return MaxStructArraySize; }

	UFUNCTION(BlueprintPure, Category = "Time Travel")
	bool ShourldRecord() const { return bShouldRecord; }
	// End public getter functions
	//////////////////////////////

	//Add to the array of timestamped recorded inputs
	UFUNCTION(BlueprintCallable, Category = "Time Travel")
	void AddTimestampedInput(float NewTimeStamp, FRecordedActionInput NewRecordedActionInput);

	// Reset all the movement and action recordings in array
	UFUNCTION(BlueprintCallable, Category = "Time Travel")
	void WipeHistory();

	UFUNCTION(BlueprintCallable, Category = "Time Travel")
	void AllowRecording(bool bNewCanRecord);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Array of structs where the timestamp entry is unique and all input values for that entry are recorded
	UPROPERTY(VisibleAnywhere, Category = "Time Travel")
	TArray<FTimestampedActions> TimestampedInputsArray;

	// Maximum "history recording" time
	UPROPERTY(EditDefaultsOnly, Category = "Time Travel")
	float MaxRecordingTime; // in seconds

	// Maximum size that the struct of recorded input actions can grow to
	UPROPERTY(EditDefaultsOnly, Category = "Time Travel")
	int MaxStructArraySize;

	// Bool to determine whether input actions should be recorded or not
	UPROPERTY(EditDefaultsOnly, Category = "Time Travel")
	bool bShouldRecord;

	// Keep track of whether the character is a past version of itself or not
	UPROPERTY(EditDefaultsOnly, Category = "Time Travel")
	bool bIsPastSelf;
};
