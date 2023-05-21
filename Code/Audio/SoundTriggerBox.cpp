// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#include "SoundTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

#include "FPSPlayer.h"

ASoundTriggerBox::ASoundTriggerBox()
{
    // Set up the box collision component
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    // Bind the OnComponentBeginOverlap event to a function
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASoundTriggerBox::OnOverlapBegin);

    // Create the audio component
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);
}

void ASoundTriggerBox::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AFPSPlayer* Player = Cast<AFPSPlayer>(OtherActor);

    if (Player == nullptr)
        return;

    // Play the assigned sound
    if (SoundToPlay)
    {
        AudioComponent->SetSound(SoundToPlay);
        AudioComponent->SetVolumeMultiplier(Volume);
        AudioComponent->Play();
    }
}
