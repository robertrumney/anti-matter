// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicManager.generated.h"

UCLASS()
class ANTIMATTERGAME_API AMusicManager : public AActor
{
    GENERATED_BODY()

public:
    AMusicManager();

protected:
    virtual void BeginPlay() override;

public:
    UAudioComponent* MusicAudioComponent;
    UAudioComponent* MonologueAudioComponent;

    UPROPERTY(EditAnywhere, Category = "Music")
        class USoundBase* MusicSound;

    UPROPERTY(EditAnywhere, Category = "Music")
        bool bLoopMusic;

    UPROPERTY(EditAnywhere, Category = "Music")
        float MusicVolume;

    UPROPERTY(EditAnywhere, Category = "Monologue")
        float MonologueVolume;

    UPROPERTY(EditAnywhere, Category = "Monologue")
        float MonologueDelay;

    UPROPERTY(EditAnywhere, Category = "Monologue")
        float MonologuePitch;

    UPROPERTY(EditAnywhere, Category = "Monologue")
        class USoundBase* MonologueSound;

    UFUNCTION(BlueprintCallable, Category = "Music")
        void PlayMusic();

    UFUNCTION(BlueprintCallable, Category = "Monologue")
        void PlayMonologue();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UAudioComponent* AudioComponent;
};
