// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#include "MusicManager.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

AMusicManager::AMusicManager()
{
    // Create the audio components
    MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));
    MonologueAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MonologueAudioComponent"));

    // Set default values
    bLoopMusic = true;
    MusicVolume = 1.0f;
    MonologueVolume = 1.0f;
}

void AMusicManager::BeginPlay()
{
    Super::BeginPlay();

    // Play the music and monologue
    PlayMusic();

    // Set a timer to call PlayMonologue after a delay
    FTimerHandle MonologueTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(MonologueTimerHandle, this, &AMusicManager::PlayMonologue, 2.0f, false);
}

void AMusicManager::PlayMusic()
{
    if (MusicSound != nullptr)
    {
        // Set music sound and loop mode
        MusicAudioComponent->SetSound(MusicSound);

        // Set music looping
        if (MusicSound->IsA<USoundWave>())
        {
            USoundWave* SoundWave = Cast<USoundWave>(MusicSound);
            SoundWave->bLooping = bLoopMusic;
        }

        // Set music volume
        MusicAudioComponent->SetVolumeMultiplier(MusicVolume);

        // Play the music
        MusicAudioComponent->Play();
    }
}

void AMusicManager::PlayMonologue()
{
    if (MonologueSound != nullptr)
    {
        // Set monologue sound and loop mode
        MonologueAudioComponent->SetSound(MonologueSound);

        // Set monolgue looping
        if (MonologueSound->IsA<USoundWave>())
        {
            USoundWave* SoundWave = Cast<USoundWave>(MonologueSound);
            SoundWave->bLooping = bLoopMusic; // Remember to change this if you want a different looping behavior for the monologue
        }

        // Set monologue volume
        MonologueAudioComponent->SetVolumeMultiplier(MonologueVolume);

        // Play the monologue
        MonologueAudioComponent->Play();
    }
}
