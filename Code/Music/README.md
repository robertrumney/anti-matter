# Music Manager

The Music Manager is a C++ class designed for managing music and monologues in a game built with Unreal Engine. It provides functionality to play music and monologues using audio components and sound assets.

## Features

- Play background music with looping and adjustable volume.
- Play monologues with looping and adjustable volume.
- Easy integration into Unreal Engine projects.
- Customizable looping behavior for music and monologues.

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
