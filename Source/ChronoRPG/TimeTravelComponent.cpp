// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "TimeTravelComponent.h"

// Default constructor for FRecordedActionInput creating an empty/null recording
FRecordedActionInput::FRecordedActionInput()
{
	RecordedAction = NAME_None;
	InputValue = 0.f;
}

// Default constructor - no implementation
// CodingRookTODO: decide if this constructor is necessary
FTimestampedActions::FTimestampedActions()
{}

FTimestampedActions::FTimestampedActions(float NewTimeStamp)
	: TimeStamp{NewTimeStamp}
{}

// Sets default values for this component's properties
UTimeTravelComponent::UTimeTravelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set member variables to default values;
	MaxRecordingTime = 600.f; // CodingRookTODO: Default of 10 minutes - is this enough?
	MaxStructArraySize = 36000; // CodingRookTODO: Default of 10 minutes - is this enough?
	bShouldRecord = true; 
}


void UTimeTravelComponent::AddTimestampedInput(float NewTimeStamp, FRecordedActionInput NewRecordedActionInput)
{
	// If this is a non-empty array
	if (TimestampedInputsArray.Num() > 0)
	{

		if (TimestampedInputsArray.Top().TimeStamp == NewTimeStamp)
		{
			TimestampedInputsArray.Top().RecordedActionInputArray.Add(NewRecordedActionInput);
			return;
		}
	}

	// Otherwise create first [recording] of new timestamp
	FTimestampedActions NewEntry;
	NewEntry.TimeStamp = NewTimeStamp;
	NewEntry.RecordedActionInputArray.Add(NewRecordedActionInput);
	TimestampedInputsArray.Add(NewEntry);
}

void UTimeTravelComponent::WipeHistory()
{
	TimestampedInputsArray.Empty();
}

void UTimeTravelComponent::AllowRecording(bool bNewCanRecord)
{
	bShouldRecord = bNewCanRecord;
}

// Called when the game starts
void UTimeTravelComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTimeTravelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

