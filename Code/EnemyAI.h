#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

class UParticleSystemComponent;

UCLASS()
class YOURPROJECT_API AEnemyAI : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AEnemyAI();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public: 
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Reference to the player character
    ACharacter* Player;

    // Particle system component for visual effect
    UParticleSystemComponent* ParticleSystem;
};
