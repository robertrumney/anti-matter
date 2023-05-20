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
    UPROPERTY(EditAnywhere, Category = "Music")
    class USoundBase* MusicSound;

    UPROPERTY(EditAnywhere, Category = "Music")
    bool bLoopMusic;

    UPROPERTY(EditAnywhere, Category = "Music")
    float MusicVolume;

    UPROPERTY(EditAnywhere, Category = "Monologue")
    float MonologueVolume;

    UFUNCTION(BlueprintCallable, Category = "Music")
    void PlayMusic();

    UFUNCTION(BlueprintCallable, Category = "Monologue")
    void PlayMonologue(class USoundBase* MonologueSound);

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UAudioComponent* AudioComponent;
};
