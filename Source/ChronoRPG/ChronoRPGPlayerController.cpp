// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "ChronoRPGPlayerController.h"
#include "ChronoRPGCharacter.h"
#include "InteractionComponentBase.h"
#include "ChronoRPGGameInstance.h"

AChronoRPGPlayerController::AChronoRPGPlayerController()
{
	// To come later
}

void AChronoRPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AChronoRPGPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AChronoRPGPlayerController::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &AChronoRPGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AChronoRPGPlayerController::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &AChronoRPGPlayerController::Turn);
	InputComponent->BindAxis("TurnRate", this, &AChronoRPGPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &AChronoRPGPlayerController::LookUp);
	InputComponent->BindAxis("LookUpRate", this, &AChronoRPGPlayerController::LookUpAtRate);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AChronoRPGPlayerController::Interact);
	InputComponent->BindAction("DropObject", IE_Pressed, this, &AChronoRPGPlayerController::DropProp);
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

void AChronoRPGPlayerController::Jump()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void AChronoRPGPlayerController::StopJumping()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
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
	}
}

void AChronoRPGPlayerController::Turn(float Value)
{
	if ((GetCharacter() != NULL) && (Value != 0.0f))
	{
		AddYawInput(Value);
	}
}

void AChronoRPGPlayerController::TurnAtRate(float Rate)
{
	if ((GetCharacter() != NULL) && (Rate != 0.0f))
	{
		AddYawInput(Rate * MyChronoRPGCharacter->BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AChronoRPGPlayerController::LookUp(float Value)
{
	if ((GetCharacter() != NULL) && (Value != 0.0f))
	{
		AddPitchInput(Value);
	}
}

void AChronoRPGPlayerController::LookUpAtRate(float Rate)
{
	if ((GetCharacter() != NULL) && (Rate != 0.0f))

	AddPitchInput(Rate * MyChronoRPGCharacter->BaseLookUpRate * GetWorld()->GetDeltaSeconds());
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
