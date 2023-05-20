// Copyright 2023 Robert Rumney Unreal Engine 48 Hour Game-Jam

#include "MyPawn.h"
#include "Engine/StaticMesh.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Enable mouse input
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bMouseLookEnabled = true; // Custom flag to enable/disable mouse look

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Create a cylinder mesh component
	UStaticMeshComponent* CylinderMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderMeshComponent"));
	CylinderMeshComponent->SetupAttachment(RootComponent);

	// Load the cylinder static mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (CylinderMeshAsset.Succeeded())
	{
		// Check if CylinderMeshComponent is valid before assigning the static mesh
		if (CylinderMeshComponent)
		{
			CylinderMeshComponent->SetStaticMesh(CylinderMeshAsset.Object);

			// Adjust the relative position of the mesh by 1 unit in the Z-axis
			CylinderMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 45.0f));

			// Set the visibility of the mesh component to false
			CylinderMeshComponent->SetVisibility(false);
		}
	}

	// Assign the cylinder mesh component to OurVisibleComponent
	OurVisibleComponent = CylinderMeshComponent;

	OurCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); // Adjust the relative position of the camera within the visible component

	// Configure the camera as a first-person perspective
	OurCamera->bUsePawnControlRotation = true;
	OurCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
	OurCamera->SetFieldOfView(90.0f); // Set the desired field of view
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle growing and shrinking based on our "Grow" action
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			// Grow to double size over the course of one second
			CurrentScale += DeltaTime;
		}
		else
		{
			// Shrink half as fast as we grow
			CurrentScale -= (DeltaTime * 0.5f);
		}
		// Make sure we never drop below our starting size, or increase past double size.
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}

	// Update the camera's location and rotation to match the pawn's
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		FRotator PawnRotation = GetActorRotation();
		FVector PawnLocation = GetActorLocation();

		if (UCameraComponent* CameraComponent = FindComponentByClass<UCameraComponent>())
		{
			FVector CameraLocation = PawnLocation + FVector(0.0f, 0.0f, 100.0f);
			CameraComponent->SetWorldLocationAndRotation(CameraLocation, PawnRotation);
		}
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Grow" key is pressed or released.
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);

	// Bind mouse input for rotation
	InputComponent->BindAxis("Turn", this, &AMyPawn::Turn);
	InputComponent->BindAxis("LookUp", this, &AMyPawn::LookUp);
}

void AMyPawn::Turn(float Value)
{
	// Update yaw rotation based on mouse movement
	AddControllerYawInput(Value);
}

void AMyPawn::LookUp(float Value)
{
	// Update pitch rotation based on mouse movement
	AddControllerPitchInput(Value);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
	const FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Direction = GetActorLocation() + FRotationMatrix(Rotation).GetUnitAxis(EAxis::X) * AxisValue;
	SetActorLocation(Direction);
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	const FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Direction = GetActorLocation() + FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y) * AxisValue;
	SetActorLocation(Direction);
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}
