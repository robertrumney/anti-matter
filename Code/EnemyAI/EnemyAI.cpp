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
	OnActorHit.AddDynamic(this, &AEnemyAI::OnHit);
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
	}
}

void AEnemyAI::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "We Hit Something");

	// Check if the OtherActor is the player pawn
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(AFPSPlayer::StaticClass())) 
	{
		// Cast the OtherActor to the player pawn class
		AFPSPlayer* PlayerCharacter = Cast<AFPSPlayer>(OtherActor); 

		// If the cast is successful
		if (PlayerCharacter) 
		{
			// Call the Die function in the player pawn class
			PlayerCharacter->Die(); 
		}
	}
}
