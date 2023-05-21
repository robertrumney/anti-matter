// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundTriggerBox.generated.h"

UCLASS()
class ANTIMATTERGAME_API ASoundTriggerBox : public AActor
{
    GENERATED_BODY()

public:
    ASoundTriggerBox();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UBoxComponent* BoxComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
        class UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
        class USoundBase* SoundToPlay;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
        float Volume;

    UFUNCTION()
        void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
            class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
