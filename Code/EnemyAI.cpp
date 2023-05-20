#include "EnemyAI.h"
#include "Kismet/GameplayStatics.h"
#include "AI/Navigation/NavigationSystem.h"
#include "AI/Navigation/NavigationPath.h"
#include "Particles/ParticleSystemComponent.h"

AEnemyAI::AEnemyAI()
{
    // Create particle system and attach it to the root component
    ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
    ParticleSystem->SetupAttachment(RootComponent);

    // Set to tick every frame
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAI::BeginPlay()
{
    Super::BeginPlay();
    
    // Obtain a reference to the player
    Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AEnemyAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Player)
    {
        UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), Player);

        if (NavPath && NavPath->PathPoints.Num() > 1)
        {
            // Get the next point on the path
            const FVector NextPathPoint = NavPath->PathPoints[1];
            
            FVector Direction = NextPathPoint - GetActorLocation();
            Direction.Normalize();
            
            // Move the AI character towards the next point on the path
            GetCharacterMovement()->AddInputVector(Direction);
        }
    }
}
