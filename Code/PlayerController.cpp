#include "PlayerController.h"
#include "GameFramework/Character.h"

void APlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Set up "movement" bindings.
    PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);

    // Set up "look" bindings.
    PlayerInputComponent->BindAxis("Turn", this, &AMyPlayerController::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &AMyPlayerController::LookUpAtRate);

    // Set up "action" bindings.
    PlayerInputComponent->BindAction("ToggleTorch", IE_Pressed, this, &AMyPlayerController::ToggleTorch);
}

void APlayerController::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();
        FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        GetCharacter()->AddMovementInput(Direction, Value);
    }
}

void APlayerController::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // find out which way is right
        FRotator Rotation = Controller->GetControlRotation();
        FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        GetCharacter()->AddMovementInput(Direction, Value);
    }
}

void APlayerController::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate);
}

void APlayerController::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate);
}

void APlayerController::ToggleTorch()
{

}
