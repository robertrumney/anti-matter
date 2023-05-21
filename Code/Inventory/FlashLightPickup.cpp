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
    AFPSPlayer* Player = Cast<AFPSPlayer>(OtherActor);

    if (Player != nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player has overlapped with the flashlight."));

        if (FlashlightActor != nullptr)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FlashlightActor is not null. Preparing to destroy..."));
            FlashlightActor->Destroy();

            FlashlightActor = nullptr;
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FlashlightActor is null. Not destroying..."));
        }

        // Destroy the pickup
        Destroy();
    }
}
