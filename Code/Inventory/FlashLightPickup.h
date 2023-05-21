// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlashLightPickup.generated.h"

UCLASS()
class ANTIMATTERGAME_API AFlashLightPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashLightPickup();

	// Define the Sphere Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USphereComponent* SphereComponent; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
		AActor* FlashlightActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// On hit event function
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool bActionPerformed = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* PickupSound;

	UAudioComponent* AudioComponent;
};
