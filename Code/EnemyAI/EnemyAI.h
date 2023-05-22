// EnemyAI.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAI.generated.h"

UCLASS()
class ANTIMATTERGAME_API AEnemyAI : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyAI();

	// The actor that EnemyAI will follow
	UPROPERTY(EditAnywhere)
		AActor* PlayerActor;

	// The time before EnemyAI starts following the player
	UPROPERTY(EditAnywhere)
		float ActivationTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ActivationTimerHandle;

	void FollowPlayer();
};
