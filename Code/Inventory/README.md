# FlashLightPickup

This repository contains the source code for a flashlight pickup feature implemented in Unreal Engine using C++. The flashlight pickup allows players to collect flashlights in the game, triggering specific actions and effects.

## Overview

The `AFlashLightPickup` class represents a flashlight pickup in the game. When the player's character collides with the flashlight pickup, it performs certain actions, such as playing a pickup sound, destroying a flashlight actor, and triggering a pickup event on the player character.

## How it Works

- The constructor of the `AFlashLightPickup` class initializes the default values and sets up the components used by the pickup.

- The `BeginPlay` function is called when the game starts or when the pickup is spawned. It binds the `OnHit` function to the `OnComponentHit` event of the sphere component.

- The `OnHit` function is triggered when the flashlight pickup collides with another object. It checks if the colliding actor is the player character. If it is, the function performs the pickup action.

- The pickup action includes the following steps:
  - It checks if the pickup action has already been performed by verifying the `bActionPerformed` flag. If it is true, indicating that the pickup action has already taken place, the function returns.
  - If the pickup action has not been performed yet, it sets `bActionPerformed` to true to prevent the pickup from being performed again.
  - It plays a sound (`PickupSound`) using the `AudioComponent`. The sound is assigned to the `AudioComponent` using the `SetSound` function and then played with the `Play` function.
  - If a flashlight actor (`FlashlightActor`) is assigned, it destroys the flashlight actor by calling the `Destroy` function on it and sets the `FlashlightActor` pointer to `nullptr`.
  - It calls the `PickupFlashlight` function on the player character (`Player`). This function is expected to handle any additional actions or effects related to the player picking up the flashlight.
  - Finally, it sets the lifespan of the pickup actor to the duration of the pickup sound, allowing the sound to finish playing before the actor is automatically destroyed.

### Copyright
Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam
