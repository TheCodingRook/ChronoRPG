// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "ChronoRPGPlayerController.h"
#include "ChronoRPGCharacter.h"
#include "InteractionComponentBase.h"
#include "ChronoRPGGameInstance.h"
#include "TimeTravelComponent.h"

AChronoRPGPlayerController::AChronoRPGPlayerController()
{
	// Sets up a time travel component/subobject
	TimeTravel = CreateDefaultSubobject<UTimeTravelComponent>(FName("Time Travel Component"));
}

void AChronoRPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	SetUpRecordableActionBinding("Jump", IE_Pressed, this, &AChronoRPGPlayerController::Jump);
	SetUpRecordableActionBinding("Jump", IE_Released, this, &AChronoRPGPlayerController::StopJumping);

	SetUpRecordableAxisBinding("MoveForward", this, &AChronoRPGPlayerController::MoveForward);
	SetUpRecordableAxisBinding("MoveRight", this, &AChronoRPGPlayerController::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	SetUpRecordableAxisBinding("Turn", this, &AChronoRPGPlayerController::Turn);
	SetUpRecordableAxisBinding("TurnRate", this, &AChronoRPGPlayerController::TurnAtRate);
	SetUpRecordableAxisBinding("LookUp", this, &AChronoRPGPlayerController::LookUp);
	SetUpRecordableAxisBinding("LookUpRate", this, &AChronoRPGPlayerController::LookUpAtRate);

	SetUpRecordableActionBinding("Interact", IE_Pressed, this, &AChronoRPGPlayerController::Interact);
	SetUpRecordableActionBinding("DropObject", IE_Pressed, this, &AChronoRPGPlayerController::DropProp);
}

void AChronoRPGPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AChronoRPGPlayerController::OnPossess(APawn* ControlledPawn)
{
	Super::OnPossess(ControlledPawn);

	MyChronoRPGCharacter = Cast<AChronoRPGCharacter>(ControlledPawn);
	if (MyChronoRPGCharacter)
	{
		MyChronoRPGCharacter->SetMyChronoRPGPlayerController(this);
	}
}

template<class UserClass>
inline void AChronoRPGPlayerController::SetUpRecordableActionBinding(const FName NewAction, const EInputEvent KeyEvent, UserClass* Object, typename FInputActionHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr Func)
{
	// First bind the action we want
	InputComponent->BindAction(NewAction, KeyEvent, Object, Func);

	// Keep track of the order in which we add movements/actions/axes in this array
	// Deal with the special case that this is a "key released" type of action; presumably we have already bound the same action for "key pressed"!
	if (KeyEvent == IE_Released)
	{
		FString NewActionString = "End" + NewAction.ToString();
		FName NewEndAction(*NewActionString);
		RecordableMovementAndActionBindings.Add(NewEndAction);
	}
	else
	{
		RecordableMovementAndActionBindings.Add(NewAction);
	}
}

template<class UserClass>
void AChronoRPGPlayerController::SetUpRecordableAxisBinding(const FName NewMovement, UserClass* Object, typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr Func)
{
	// First bind the axis movements we want
	InputComponent->BindAxis(NewMovement, Object, Func);

	// Keep track of the order in which we add movements/actions/axes in this array
	RecordableMovementAndActionBindings.Add(NewMovement);
}


void AChronoRPGPlayerController::RecordAction(FName ActionToRecord, float Value)
{
	// Record the action or movement in TimeTravelComponent
	if (ensure(TimeTravel != nullptr))
	{
		if (TimeTravel->ShourldRecord())
		{
			// Record new action and its associated value
			// CAUTION: Make sure you use the same name to describe the action / movement
			FRecordedActionInput NewRecordedActionInput;
			NewRecordedActionInput.RecordedAction = ActionToRecord;
			NewRecordedActionInput.InputValue = Value;

			TimeTravel->AddTimestampedInput(GetWorld()->GetTimeSeconds(), NewRecordedActionInput);
		}
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s did not have a valid TimeTravelComponent!"), *GetName())
	}
}

void AChronoRPGPlayerController::Jump()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
		RecordAction("Jump", 1.f);
	}
}

void AChronoRPGPlayerController::StopJumping()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
		RecordAction("EndJump", 1.f);
	}
}

void AChronoRPGPlayerController::MoveForward(float Value)
{
	if ((GetCharacter() != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		GetCharacter()->AddMovementInput(Direction, Value);
		RecordAction("MoveForward", Value);
	}
}

void AChronoRPGPlayerController::MoveRight(float Value)
{
	if ((GetCharacter() != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		GetCharacter()->AddMovementInput(Direction, Value);
		RecordAction("MoveRight", Value);
	}
}

void AChronoRPGPlayerController::Turn(float Value)
{
	if ((GetCharacter() != NULL) && (Value != 0.0f))
	{
		AddYawInput(Value);
		RecordAction("Turn", Value);
	}
}

void AChronoRPGPlayerController::TurnAtRate(float Rate)
{
	if ((GetCharacter() != NULL) && (Rate != 0.0f))
	{
		AddYawInput(Rate * MyChronoRPGCharacter->BaseTurnRate * GetWorld()->GetDeltaSeconds());
		RecordAction("TurnAtRate", Rate);
	}
}

void AChronoRPGPlayerController::LookUp(float Value)
{
	if ((GetCharacter() != NULL) && (Value != 0.0f))
	{
		AddPitchInput(Value);
		RecordAction("LookUp", Value);
	}
}

void AChronoRPGPlayerController::LookUpAtRate(float Rate)
{
	if ((GetCharacter() != NULL) && (Rate != 0.0f))

	AddPitchInput(Rate * MyChronoRPGCharacter->BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	RecordAction("LookUpAtRate", Rate);
}

void AChronoRPGPlayerController::Interact()
{
	if (GetMyChronoRPGCharacter())
	{
		if (UInteractionComponentBase* InteractionToExecute = Cast<UChronoRPGGameInstance>(GetGameInstance())->GetLatestInteractionCommand())
		{
			InteractionToExecute->ExecuteInteraction(MyChronoRPGCharacter);
		}
	}
}

void AChronoRPGPlayerController::DropProp()
{
	MyChronoRPGCharacter->DropProp();
}
