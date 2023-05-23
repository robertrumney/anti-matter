// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "EnemyAI.generated.h"

UCLASS()
class ANTIMATTERGAME_API AEnemyAI : public AController
{
	GENERATED_BODY()

public:
	AEnemyAI();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void FollowPlayer();

	bool bIsActive = false;

	UPROPERTY(EditAnywhere, Category = "EnemyAI")
		float ActivationTime;

	UPROPERTY(EditAnywhere, Category = "EnemyAI")
		AActor* PlayerActor;

	UPROPERTY(EditAnywhere, Category = "EnemyAI")
		AActor* EnemyActor;

};
