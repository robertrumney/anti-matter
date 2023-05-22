// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#include "EnemyAI.h"
#include "Kismet/GameplayStatics.h"

AEnemyAI::AEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ActivationTimerHandle, this, &AEnemyAI::StartTicking, ActivationTime, false);
}

void AEnemyAI::StartTicking()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PrimaryActorTick.bCanEverTick)
	{
		FollowPlayer();
	}
}

void AEnemyAI::FollowPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hi, it's meeeeeep!");

	if (PlayerActor && EnemyActor)
	{
		FVector Direction = PlayerActor->GetActorLocation() - EnemyActor->GetActorLocation();
		Direction.Normalize();

		float DeltaTime = GetWorld()->GetDeltaSeconds();
		EnemyActor->SetActorLocation(EnemyActor->GetActorLocation() + Direction * 100 * DeltaTime);
	}
}
