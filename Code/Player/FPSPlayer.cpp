// Copyright 2023 Robert Rumney Unreal Engine 48 Hour Game-Jam

#include "FPSPlayer.h"
#include "Engine/StaticMesh.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
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

	UE_LOG(LogTemp, Error, TEXT("This is a warning message"));

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
			//CylinderMeshComponent->SetVisibility(false);

			// Enable collision and physics simulation
			CylinderMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			CylinderMeshComponent->SetSimulatePhysics(true);

			// Adjust collision response
			CylinderMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

			// Set the collision profile
			CylinderMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

			// Set the relative location and rotation
			CylinderMeshComponent->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

			UE_LOG(LogTemp, Error, TEXT("Did the damn thing"));
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
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	else
	{
		HeadBobTimer = 0;
	}

	// Update camera location with headbob offset
	if (UCameraComponent* CameraComponent = FindComponentByClass<UCameraComponent>())
	{
		FVector CameraLocation = GetActorLocation() + FVector(0.0f, 0.0f, 250.0f) + HeadBobOffset;
		CameraComponent->SetWorldLocationAndRotation(CameraLocation, GetActorRotation());

		// Perform lerping if zooming is active
		if (bIsZooming)
		{
			if (LerpingAlpha < MaxZoom)
				LerpingAlpha += DeltaTime;

			float LerpedFOV = FMath::Lerp(InitialFOV, ZoomedInFOV, LerpingAlpha);
			CameraComponent->SetFieldOfView(LerpedFOV);
		}
		else
		{
			// Perform lerping for zooming out when not active
			if (LerpingAlpha > 0.0f)
			{
				LerpingAlpha -= DeltaTime;
				float LerpedFOV = FMath::Lerp(InitialFOV, ZoomedInFOV, LerpingAlpha);
				CameraComponent->SetFieldOfView(LerpedFOV);
			}
		}
	}
}

// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &AFPSPlayer::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AFPSPlayer::Move_YAxis);

	// Bind mouse input for rotation
	InputComponent->BindAxis("Turn", this, &AFPSPlayer::Turn);
	InputComponent->BindAxis("LookUp", this, &AFPSPlayer::LookUp);

	// Bind the right mouse button press event
	InputComponent->BindAction("RightMouseButton", IE_Pressed, this, &AFPSPlayer::OnRightMouseButtonDown);

	// Bind the right mouse button release event
	InputComponent->BindAction("RightMouseButton", IE_Released, this, &AFPSPlayer::OnRightMouseButtonUp);
}

void AFPSPlayer::Turn(float Value)
{
	// Update yaw rotation based on mouse movement
	AddControllerYawInput(Value);
}

void AFPSPlayer::LookUp(float Value)
{
	// Update pitch rotation based on mouse movement
	AddControllerPitchInput(Value);
}

void AFPSPlayer::Move_XAxis(float AxisValue)
{
	const FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X) * AxisValue * MovementSpeed;
	AddActorWorldOffset(Direction);
	CurrentVelocity.X = AxisValue;
}

void AFPSPlayer::Move_YAxis(float AxisValue)
{
	const FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y) * AxisValue * MovementSpeed;
	AddActorWorldOffset(Direction);
	CurrentVelocity.Y = AxisValue;
}

// Function to handle right mouse button press
void AFPSPlayer::OnRightMouseButtonDown()
{
	bIsZooming = true;

	if (UCameraComponent* CameraComponent = FindComponentByClass<UCameraComponent>())
	{
		InitialFOV = CameraComponent->FieldOfView;
	}

	LerpingAlpha = 0.0f;
}

// Function to handle right mouse button release
void AFPSPlayer::OnRightMouseButtonUp()
{
	bIsZooming = false;
}
