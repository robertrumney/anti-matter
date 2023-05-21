# Music Manager

The Music Manager is a C++ class designed managing music and monologues with a drag and drop interface within the Unreal Engine C++ 48 Hour Game-Jam

## Features

- Play background music with looping and adjustable volume.
- Simultaneously play & mix voice monologues or SFX from the same actor with looping and adjustable volume.
- Easy integration into Unreal Engine projects.
- Customizable looping behavior for music

## Usage

1. Add the Music Manager to the scene.
2. Assign music and monologue sound assets to the Music Manager in the editor.
3. Customize the looping behavior, music volume, and monologue volume as desired.
4. Run the game 

## How it Works

The Music Manager class is implemented using Unreal Engine's audio components and sound assets. Here's a breakdown of how it works:

- The Music Manager class provides two audio components: MusicAudioComponent for playing the background music and MonologueAudioComponent for playing the monologues.
- When the game starts, the BeginPlay() function is called. It immediately plays the music and sets a timer to play the monologue after a delay.
- The PlayMusic() function is responsible for playing the music. It checks if a music sound asset is assigned, sets the sound, looping behavior, volume, and plays it using the MusicAudioComponent.
- The PlayMonologue() function is similar to PlayMusic() but handles the monologue sound asset using the MonologueAudioComponent.
- To use the Music Manager, you need to create an instance of the class, assign music and monologue sound assets, and customize the looping behavior, music volume, and monologue volume if desired.
- Once the setup is complete, you can call the PlayMusic() and PlayMonologue() functions to start playing the music and monologue in your game.

## Example

```cpp
// Create an instance of the Music Manager
AMusicManager* MusicManager = GetWorld()->SpawnActor<AMusicManager>();

// Assign music and monologue sound assets to the Music Manager
MusicManager->MusicSound = MusicSoundAsset;
MusicManager->MonologueSound = MonologueSoundAsset;

// Customize the looping behavior, music volume, and monologue volume if desired
MusicManager->bLoopMusic = true;
MusicManager->MusicVolume = 0.8f;
MusicManager->MonologueVolume = 0.5f;

// Play the music and monologue
MusicManager->PlayMusic();
MusicManager->PlayMonologue();
```

## Note

In this example we delay the monologue start by 2 seconds
```cpp
void AMusicManager::BeginPlay()
{
    Super::BeginPlay();

    // Play the music and monologue
    PlayMusic();

    // Set a timer to call PlayMonologue after a delay
    FTimerHandle MonologueTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(MonologueTimerHandle, this, &AMusicManager::PlayMonologue, 2.0f, false);
}
```

### Copyright
Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam
