// Copyright 2023 Robert Rumney Unreal Engine 48 Hour Game-Jam

#include "FPSPlayer.h"
#include "FlashLight.h" 

#include "Engine/StaticMesh.h"
#include "Camera/CameraComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"

#include "GameFramework/Controller.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"

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

	// Create a camera and attach to root
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(RootComponent);

	// Adjust the relative position of the camera within the visible component
	OurCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f)); 

	// Configure the camera as a first-person perspective
	OurCamera->bUsePawnControlRotation = true;
	OurCamera->SetProjectionMode(ECameraProjectionMode::Perspective);
	OurCamera->SetFieldOfView(90.0f); // Set the desired field of view

	// Create the CapsuleComponent
	//UCapsuleComponent* CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyCapsuleComponent"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MyCapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);

	// Set the CapsuleComponent as the root component
	RootComponent = CapsuleComponent;

	// Enable physics simulation for the CapsuleComponent
	CapsuleComponent->SetSimulatePhysics(true);

	// Make collision settings editable in the inspector
	CapsuleComponent->SetCollisionProfileName(TEXT("BlockAll"));  // Set collision profile
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);  // Set collision enabled to PhysicsOnly
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);  // Set collision response
	CapsuleComponent->SetCollisionObjectType(ECC_Pawn);  // Set collision object type
	CapsuleComponent->SetGenerateOverlapEvents(true);  // Enable overlap events
	CapsuleComponent->SetCanEverAffectNavigation(true);  // Enable navigation interaction
	CapsuleComponent->SetEnableGravity(true);  // Enable gravity
	CapsuleComponent->bApplyImpulseOnDamage = true;  // Enable impulse on damage
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
		//float BobSpeed = 10.0f; // Adjust the speed of the headbob motion
		float BobSpeed = 2.5f * MovementSpeed;
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
		FVector CameraLocation = GetActorLocation() + FVector(0.0f, 0.0f, 200.0f) + HeadBobOffset;
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

	// Inside AFPSPlayer::SetupPlayerInputComponent
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSPlayer::BeginSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFPSPlayer::EndSprint);
}

void AFPSPlayer::BeginSprint()
{
	// Increase movement speed
	MovementSpeed = SprintingMovementSpeed;
}

void AFPSPlayer::EndSprint()
{
	// Decrease movement speed
	MovementSpeed = DefaultMovementSpeed;
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
	if (AxisValue == 0.f) 
	{
		CurrentVelocity.X = 0;
	}
	else 
	{
		const FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X) * AxisValue * MovementSpeed;
		AddActorWorldOffset(Direction, true);  // Added sweeping for collision detection
		CurrentVelocity.X = AxisValue;
	}
}

void AFPSPlayer::Move_YAxis(float AxisValue)
{
	if (AxisValue == 0.f) 
	{
		CurrentVelocity.Y = 0;
	}
	else 
	{
		const FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y) * AxisValue * MovementSpeed;
		AddActorWorldOffset(Direction, true);  // Added sweeping for collision detection
		CurrentVelocity.Y = AxisValue;
	}
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

void AFPSPlayer::PickupFlashLight()
{
	if (!bHasFlashlight)
	{
		// Spawn the flashlight actor at the player's location
		FlashLight = GetWorld()->SpawnActor<AFlashLight>(AFlashLight::StaticClass(), GetActorTransform());
		bHasFlashlight = true;
	}
}

void AFPSPlayer::Die()
{
	// Restart the level
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}
