#include "FlashLightPickup.h"
#include "Components/SphereComponent.h"
#include "FPSPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlashLightPickup::AFlashLightPickup()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;
    SphereComponent->SetSphereRadius(100.0f);
    SphereComponent->SetSimulatePhysics(true); // Enable physics simulation
    SphereComponent->SetNotifyRigidBodyCollision(true); // Ensure it generates hit events
}

// Called when the game starts or when spawned
void AFlashLightPickup::BeginPlay()
{
    Super::BeginPlay();
    
    SphereComponent->OnComponentHit.AddDynamic(this, &AFlashLightPickup::OnHit); // Bind the OnHit function
}

void AFlashLightPickup::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Log a message to ensure the hit event is firing
    UE_LOG(LogTemp, Warning, TEXT("FlashLightPickup has been hit."));

    AFPSPlayer* Player = Cast<AFPSPlayer>(OtherActor);

    if (Player)
    {
        // Do something when the player hits the flashlight pickup
        UE_LOG(LogTemp, Warning, TEXT("Player has hit the flashlight pickup."));
    }
}
