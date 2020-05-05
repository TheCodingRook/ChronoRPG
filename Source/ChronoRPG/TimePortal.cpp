// Copyright 2020. All rights reserved. A game prototype by CodingRook.


#include "TimePortal.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/TextRenderComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATimePortal::ATimePortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the default root component
	DefaultRoot = CreateDefaultSubobject<USceneComponent>("Default Root");
	SetRootComponent(DefaultRoot);

	// Set up the bounds volume for the time portal
	PortalTrigger = CreateDefaultSubobject<UBoxComponent>("Portal Frame");
	PortalTrigger->SetupAttachment(DefaultRoot);
	PortalTrigger->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	

	// Set up the allowthrough toggle volume for the time portal
	AllowThroughToggle = CreateDefaultSubobject<UBoxComponent>("Through Access");
	AllowThroughToggle->SetupAttachment(PortalTrigger);
	AllowThroughToggle->SetRelativeLocation(FVector(0.f, 0.f, -10.f));

	// Set up the mesh to project the portal's viewpoint on
	PortalScreen = CreateDefaultSubobject<UStaticMeshComponent>("Portal Screeen");
	PortalScreen->SetupAttachment(PortalTrigger);
	PortalScreen->SetCastShadow(false);

	// Set up the spawn point for this time portal and its "helper" children components
	TeleportLocation = CreateDefaultSubobject<USceneComponent>("Teleport Location");
	TeleportLocation->SetupAttachment(DefaultRoot);
	TeleportLocation->SetRelativeLocation(FVector(0.f, -1000.f, -100.f));
	TeleportLocation->SetRelativeRotation(FRotator(0.f, 50.f, 0.f));


	// Set up the portal's arrow component to help with placement in the Editor
	TeleportLocationArrow = CreateDefaultSubobject<UArrowComponent>("Spawn Direction");
	TeleportLocationArrow->SetupAttachment(TeleportLocation);
	TeleportLocationArrow->SetRelativeLocation(FVector(70.f, 0.f, 40.f));
	TeleportLocationArrow->SetRelativeRotation(FRotator(-30.f, 180.f, 0.f));

	// Set up a text label for the spawn point so it is visible in the Editor (but not in game obviously!)
	TeleportLocationText = CreateDefaultSubobject<UTextRenderComponent>("Spawn Point Label");
	TeleportLocationText->SetupAttachment(TeleportLocation);
	TeleportLocationText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	TeleportLocationText->SetText(FText::FromString("Teleport spawn point"));
	TeleportLocationText->SetHiddenInGame(true);
	// Some formatting here...
	TeleportLocationText->SetWorldSize(50.f);
	TeleportLocationText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TeleportLocationText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);

	// Set up the the portal's scene capture
	PortalSceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Portal SceneCapture");
	PortalSceneCapture->SetupAttachment(TeleportLocation);
	PortalSceneCapture->SetRelativeLocation(FVector(0.f, 0.f, 75.f));
	PortalSceneCapture->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

}

// Called when the game starts or when spawned
void ATimePortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

