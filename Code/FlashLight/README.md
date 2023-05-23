# Simple Flashlight

This code defines a simple class AFlashLight which uses a simple spotlight for a torch for the Unreal Engine C++ 48 Hour Game-Jam. No mesh is being used for this example, but will be added in later iterations!

## Constructor:

The constructor AFlashLight::AFlashLight() initializes the flashlight actor, sets up the primary tick functionality, creates a USpotLightComponent for the flashlight's lighting effect, and attaches this spot light to the root component of the flashlight actor.

## Toggle Function:

The ToggleFlashlight() function simply toggles the visibility of the flashlight's spot light.

## BeginPlay Function:

In the BeginPlay() function, it gets the player pawn (if it exists) and checks if it's of the type AFPSPlayer (a specific type of character in the game, likely a subclass of APawn). If it is, it attaches the flashlight to the player character.

## Tick Function:

In the Tick() function, the code gets the player pawn again and checks if it's locally controlled (to ensure the flashlight's direction is updated for the local player). If it is, it retrieves the current viewpoint (camera location and rotation) of the player. The flashlight's direction (spotlight rotation) is then set to match the player's viewpoint, and the intensity of the light is set.

## Copyright
Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam
