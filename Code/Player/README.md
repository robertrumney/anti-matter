# FPS Player Character - Unreal Engine 48-Hour Game Jam

This repository contains the code for a first-person player character implemented in Unreal Engine. The player character is designed for a game developed within a 48-hour game jam.

## Overview

The FPS Player character is a basic implementation of a first-person perspective player character. It includes features such as camera control, movement, sprinting, zooming, and interaction with a flashlight.

## Features

- Camera Control: The player character's camera is controlled by mouse movement, allowing the player to look around the environment.
- Movement: The player character can move in the X and Y axes using the keyboard inputs.
- Sprinting: The player character can sprint by pressing and holding a designated key, increasing the movement speed.
- Head Bobbing: The player character's camera applies a head bobbing effect when the player is moving.
- Zooming: The player can zoom in by pressing the right mouse button, which changes the camera's field of view.
- Flashlight Interaction: The player character can pick up a flashlight by interacting with it in the game world.

# Implementation Details

## Camera Control

- The camera component is created and attached to the root component of the player character.
- Mouse input is used to control the rotation of the camera, updating the yaw and pitch rotation values.

## Movement

- The player character's movement is implemented using the AddActorWorldOffset function, allowing movement in the X and Y axes.
- Keyboard inputs for movement are bound to the "MoveX" and "MoveY" axes.
- The player character's movement speed can be adjusted.
- Sprinting functionality is implemented by increasing the movement speed when the designated sprint key is pressed.

## Head Bobbing

- The player character's camera applies a head bobbing effect when the player is moving.
- The head bobbing effect is based on the player's movement speed and is calculated using a sinusoidal function.
- The head bobbing effect provides a more immersive experience and adds realism to the player's movement.

## Zooming

- The player character can zoom in by pressing the right mouse button.
- Zoom functionality is implemented by lerping the camera's field of view between the initial field of view and a zoomed-in field of view.
- The lerping is performed every frame while the zoom button is pressed, providing a smooth transition.

## Flashlight Interaction

- The player character can interact with a flashlight in the game world.
- The PickupFlashLight function allows the player character to pick up the flashlight, spawning a flashlight actor at the player's location.
- A boolean flag is used to track whether the player character has picked up the flashlight.

### Copyright
// Copyright 2023 Robert Rumney Unreal Engine 48 Hour Game-Jam
