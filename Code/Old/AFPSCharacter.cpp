#include "AFPSCharacter.h"
#include "Components/InputComponent.h"

// Sets default values
AAFPSCharacter::AAFPSCharacter()
{
    // Set this pawn to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create a first person camera component
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    // Attach the camera component to our capsule component
    FirstPersonCameraComponent->SetupAttachment(GetRootComponent());

    // Create the torch as a spotlight component
    Torch = CreateDefaultSubobject<USpotLightComponent>(TEXT("Torch"));
    Torch->SetupAttachment(FirstPersonCameraComponent);
    Torch->Intensity = 5000.0f; // Example intensity, adjust as needed
    Torch->SetVisibility(false); // Start off

    // Set initial player stats
    Health = 100.0f;
    Sanity = 100.0f;

    // Set initial torch state
    bIsTorchOn = false;
}

// Called when the game starts or when spawned
void AAFPSCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AAFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind our "ToggleTorch" action to the ToggleTorch function
    PlayerInputComponent->BindAction("ToggleTorch", IE_Pressed, this, &AAFPSCharacter::ToggleTorch);
}

void AAFPSCharacter::ToggleTorch()
{
    // Toggle the torch's state
    bIsTorchOn = !bIsTorchOn;

    // Set the torch visibility to match the new state
    Torch->SetVisibility(bIsTorchOn);
}
