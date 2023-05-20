#include "MusicManager.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

AMusicManager::AMusicManager()
{
    // Create the audio component
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    RootComponent = AudioComponent;

    // Set default values
    bLoopMusic = true;
    MusicVolume = 1.0f;
    MonologueVolume = 1.0f;
}

void AMusicManager::BeginPlay()
{
    Super::BeginPlay();

    // Play the music
    PlayMusic();
}

void AMusicManager::PlayMusic()
{
    if (MusicSound != nullptr)
    {
        // Set music sound and loop mode
        AudioComponent->SetSound(MusicSound);
        AudioComponent->SetLooping(bLoopMusic);

        // Set music volume
        AudioComponent->SetVolumeMultiplier(MusicVolume);

        // Play the music
        AudioComponent->Play();
    }
}

void AMusicManager::PlayMonologue(USoundBase* MonologueSound)
{
    if (MonologueSound != nullptr)
    {
        // Stop any currently playing monologue
        AudioComponent->Stop();

        // Set monologue sound and loop mode
        AudioComponent->SetSound(MonologueSound);
        AudioComponent->SetLooping(false);

        // Set monologue volume
        AudioComponent->SetVolumeMultiplier(MonologueVolume);

        // Play the monologue
        AudioComponent->Play();
    }
}
