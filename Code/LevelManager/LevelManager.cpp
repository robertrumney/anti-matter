#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
ALevelManager::ALevelManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts
void ALevelManager::BeginPlay()
{
    Super::BeginPlay();

    // Iterate over all actions
    for (FGameAction& Action : Actions)
    {
        // If delay is zero, perform action immediately
        if (Action.Delay <= 0.0f)
        {
            PerformAction(Action);
        }
        else
        {
            // Add the action to our pending actions
            this->PendingActions.Add(Action);

            // Schedule action for future
            FGameAction PendingAction = this->PendingActions.Last();
            GetWorld()->GetTimerManager().SetTimer(
                PendingAction.TimerHandle,
                [this, PendingAction]() mutable
                {
                    PerformAction(PendingAction);
                    this->PendingActions.Remove(PendingAction);
                },
                Action.Delay,
                false
            );
        }
    }
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALevelManager::PerformAction(FGameAction Action)
{
    // Check if the action's target actor is valid
    if (Action.TargetActor)
    {
        // Perform action as defined in the struct

        // Make actor invisible
        if (Action.bShouldInvisible)
        {
            Action.TargetActor->SetActorHiddenInGame(true);
        }

        // Play sound before destroying actor
        if (Action.Sound)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), Action.Sound, Action.TargetActor->GetActorLocation());
        }

        // Destroy actor
        if (Action.bShouldDestroy)
        {
            Action.TargetActor->Destroy();
        }
    }
}
