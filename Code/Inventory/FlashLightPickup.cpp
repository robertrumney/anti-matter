// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#include "FlashLightPickup.h"
#include "FPSPlayer.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AFlashLightPickup::AFlashLightPickup()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;
    SphereComponent->SetSphereRadius(100.0f);
    SphereComponent->SetSimulatePhysics(true); // Enable physics simulation
    SphereComponent->SetNotifyRigidBodyCollision(true); // Ensure it generates hit events

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->bAutoActivate = false; // Do not play the sound immediately when the game starts
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
        if (bActionPerformed)
            return;

        bActionPerformed = true;

        // Play the pickup sound
        if (PickupSound != nullptr)
        {
            AudioComponent->SetSound(PickupSound);
            AudioComponent->Play();
        }

        if (FlashLightActor != nullptr)
        {
            FlashLightActor->Destroy();
            FlashLightActor = nullptr;
        }

        Player->PickupFlashLight();

        //  // Destroy the pickup after a delay to allow the sound to finish playing
        SetLifeSpan(PickupSound->Duration);
    }
}
