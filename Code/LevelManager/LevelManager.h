// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

USTRUCT(BlueprintType)
struct FGameAction
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere)
        float Delay;

    UPROPERTY(EditAnywhere)
        AActor* TargetActor;

    UPROPERTY(EditAnywhere)
        USoundBase* Sound;

    UPROPERTY(EditAnywhere)
        bool bShouldDestroy;

    UPROPERTY(EditAnywhere)
        bool bShouldInvisible;

    FTimerHandle TimerHandle;

    // Define both operator== and operator!=.
    bool operator==(const FGameAction& other) const
    {
        return Delay == other.Delay &&
            TargetActor == other.TargetActor &&
            Sound == other.Sound &&
            bShouldDestroy == other.bShouldDestroy &&
            bShouldInvisible == other.bShouldInvisible;
    }

    bool operator!=(const FGameAction& other) const {
        return !(*this == other);
    }
};

UCLASS()
class ANTIMATTERGAME_API ALevelManager : public AActor
{
    GENERATED_BODY()

public:
    ALevelManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Game Actions")
        TArray<FGameAction> Actions;

    // Declaration in header file
    void PerformAction(FGameAction Action);

    TArray<FGameAction> PendingActions;
};
