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

	// Increment headbob timer based on player's movement
	HeadBobTimer += CurrentVelocity.Size() * DeltaTime;

	// Calculate headbob offset
	FVector HeadBobOffset = FVector(0.0f, 0.0f, 0.0f);


	if (!CurrentVelocity.IsZero())
	{
		float BobSpeed = 10.0f; // Adjust the speed of the headbob motion
		float BobAmount = 5.0f; // Adjust the amount of headbob motion
		float HeadBobAmount = FMath::Lerp(-BobAmount, BobAmount, FMath::Sin(HeadBobTimer * BobSpeed));

		HeadBobOffset.Z = HeadBobAmount;
	}

	// Update camera location with headbob offset
	if (UCameraComponent* CameraComponent = FindComponentByClass<UCameraComponent>())
	{
		FVector CameraLocation = GetActorLocation() + FVector(0.0f, 0.0f, 250.0f) + HeadBobOffset;
		CameraComponent->SetWorldLocationAndRotation(CameraLocation, GetActorRotation());
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

	// Bind the right mouse button press event
	PlayerInputComponent->BindAction("RightMouseButton", IE_Pressed, this, &AMyPawn::OnRightMouseButtonDown);

	// Bind the right mouse button release event
	PlayerInputComponent->BindAction("RightMouseButton", IE_Released, this, &AMyPawn::OnRightMouseButtonUp);
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
	const FVector Direction = GetActorLocation() + FRotationMatrix(Rotation).GetUnitAxis(EAxis::X) * AxisValue * MovementSpeed;
	SetActorLocation(Direction);
	CurrentVelocity.X = AxisValue;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	const FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Direction = GetActorLocation() + FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y) * AxisValue;
	SetActorLocation(Direction);
	CurrentVelocity.Y = AxisValue;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}

// Function to handle right mouse button press
void AMyPawn::OnRightMouseButtonDown()
{
	bIsZooming = true;
	
	if (UCameraComponent* CameraComponent = FindComponentByClass<UCameraComponent>())
	{
		InitialFOV = CameraComponent->FieldOfView;
	}

	LerpingAlpha = 0.0f;
}

// Function to handle right mouse button release
void AMyPawn::OnRightMouseButtonUp()
{
	bIsZooming = false;
	LerpingAlpha = 0.0f;
}
