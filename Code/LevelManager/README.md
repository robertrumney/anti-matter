# Level Manager

The Level Manager script is designed to provide a convenient way to manage and execute various actions within a game level in Unreal Engine. It allows you to define actions, such as making actors invisible, playing sounds, and destroying actors, and schedule them to occur either immediately or after a specified delay.

## Purpose

The purpose of the Level Manager is to automate the execution of game actions within a level. Instead of manually triggering actions in the game code or through blueprint scripting, the Level Manager allows you to define actions and their properties in a centralized location. This provides flexibility and ease of maintenance, as you can modify or add new actions without having to modify multiple sections of code or blueprints.

## How It Works

The Level Manager is implemented as an Unreal Engine actor class (`ALevelManager`) that can be placed in the game level. It utilizes a struct (`FGameAction`) to define individual actions and their properties. Here's how the script works:

1. When the game starts, the `BeginPlay` function of the `ALevelManager` is called.
2. The script iterates over all defined actions and checks if each action should be performed immediately or after a delay.
3. If the delay is zero or negative, the action is performed immediately by calling the `PerformAction` function.
4. If the delay is greater than zero, the action is added to the `PendingActions` array and scheduled to occur in the future using a timer. The timer triggers a lambda function that performs the action and removes it from the `PendingActions` array.
5. The `Tick` function is called every frame but doesn't perform any specific actions in this script.
6. The `PerformAction` function is responsible for executing the specified action on the target actor.
   - It first checks if the target actor is valid.
   - If valid, it performs the action based on the properties defined in the `FGameAction` struct.
     - If the `bShouldInvisible` property is true, it makes the actor invisible by calling `SetActorHiddenInGame(true)` on the target actor.
     - If the `Sound` property is not null, it plays the specified sound at the location of the target actor using `UGameplayStatics::PlaySoundAtLocation`.
     - If the `bShouldDestroy` property is true, it destroys the target actor.
     - More properties to be added soon!

By using the Level Manager, or even multiple instances of LevelManager - you can easily define and schedule actions to be executed within a game level, adding more dynamism and automation to your game experience.

### Copyright
Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam
