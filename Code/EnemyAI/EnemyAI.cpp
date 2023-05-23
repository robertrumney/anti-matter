// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#include "EnemyAI.h"
#include "FPSPlayer.h"

AEnemyAI::AEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ActivationTime < 0)
		FollowPlayer();
	else
		ActivationTime -= DeltaTime;
}

void AEnemyAI::FollowPlayer()
{
	if (PlayerActor && EnemyActor)
	{
		FVector Direction = PlayerActor->GetActorLocation() - EnemyActor->GetActorLocation();
		Direction.Normalize();

		FVector StartLocation = EnemyActor->GetActorLocation();
		FVector EndLocation = StartLocation + (Direction * 1000.0f);
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		// Ignore self for raycast
		CollisionParams.AddIgnoredActor(EnemyActor); 

		// Perform the raycast
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_WorldStatic, CollisionParams);

		if (bHit)
		{
			// An obstacle is detected, calculate the avoidance direction
			FVector AvoidanceDirection = FVector::CrossProduct(HitResult.ImpactNormal, FVector::UpVector);
			AvoidanceDirection.Normalize();

			// Adjust the movement direction by combining avoidance and player direction
			Direction = (Direction + AvoidanceDirection).GetSafeNormal();
		}

		// Rotate to look at the player
		float RotationInterpSpeed = 2;

		FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		EnemyActor->SetActorRotation(FMath::RInterpTo(EnemyActor->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), RotationInterpSpeed));

		// Move towards the player
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		EnemyActor->SetActorLocation(EnemyActor->GetActorLocation() + Direction * 100 * DeltaTime);

		// Calculate the distance to the player
		if (PlayerActor && EnemyActor)
		{
			float Distance = FVector::Dist(EnemyActor->GetActorLocation(), PlayerActor->GetActorLocation());

			// If the distance is less than a certain value, kill the player
			if (Distance < 1.0f)
			{
				AFPSPlayer* PlayerCharacter = Cast<AFPSPlayer>(PlayerActor);

				if (PlayerCharacter)
				{
					PlayerCharacter->Die();
				}
			}
		}
	}
}
