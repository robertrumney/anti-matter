# Enemy AI

This repository contains the source code for an enemy AI implementation in Unreal Engine using C++. The AI is designed to make the enemy character follow and attack the player character.

## Code Explanation

The `EnemyAI` class in the code is responsible for implementing the enemy AI behavior. Here's a breakdown of what the code does:

- The `EnemyAI` constructor sets the `PrimaryActorTick.bCanEverTick` property to `true`, enabling the `Tick` function to be called every frame.

- In the `BeginPlay` function, the enemy AI's initialization logic can be implemented. This function is called when the actor is first spawned in the game world.

- The `Tick` function is called every frame. It checks if the `ActivationTime` is less than 0. If true, it calls the `FollowPlayer` function; otherwise, it decreases the `ActivationTime` by the delta time.

- The `FollowPlayer` function is responsible for making the enemy AI follow the player character in the game world.

  - It calculates the direction from the enemy actor to the player actor by subtracting their locations and normalizing the resulting vector.

  - It performs a line trace from the enemy actor's location towards the player actor to check for obstacles. If an obstacle is detected, it calculates an avoidance direction based on the impact normal and adjusts the movement direction by combining the avoidance direction and the player direction.

  - It rotates the enemy actor to look at the player by interpolating the current rotation towards the target rotation.

  - It moves the enemy actor towards the player by updating its location based on the movement direction.

  - It calculates the distance between the enemy actor and the player actor. If the distance is less than 1.0f, it assumes that the enemy has caught up with the player and attempts to kill the player by calling the `Die` function on the player character.
