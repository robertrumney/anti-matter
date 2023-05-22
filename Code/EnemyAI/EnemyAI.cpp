// EnemyAI.cpp

#include "EnemyAI.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyAI::AEnemyAI()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	// Set up a timer to call the FollowPlayer function after ActivationTime seconds
	GetWorld()->GetTimerManager().SetTimer(ActivationTimerHandle, this, &AEnemyAI::FollowPlayer, ActivationTime);
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAI::FollowPlayer()
{
	// Check if the PlayerActor exists
	if (PlayerActor)
	{
		// Get the direction to the player
		FVector Direction = PlayerActor->GetActorLocation() - GetActorLocation();
		Direction.Normalize();

		// Move towards the player
		SetActorLocation(GetActorLocation() + Direction * 100 * GetWorld()->GetDeltaSeconds());
	}
}
