// Copyright 2023 Robert Rumney Unreal Engine 48 Hour Game-Jam

#pragma once
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSPlayer.generated.h"

UCLASS()
class ANTIMATTERGAME_API AFPSPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Components")
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		float CollisionSphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		float CollisionCapsuleRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		float CollisionCapsuleHalfHeight;

	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void OnRightMouseButtonUp();
	void OnRightMouseButtonDown();

	//Input variables
	FVector CurrentVelocity;
	bool bGrowing;
	bool bMouseLookEnabled;
	float MovementSpeed = 4;

	float HeadBobTimer;

	// Declare a variable to store the initial camera FOV
	float InitialFOV;

	// Declare a variable to store the target zoomed-in FOV
	float ZoomedInFOV = 60.0f;
	float MaxZoom = 2;

	// Declare a variable to store the lerping alpha
	float LerpingAlpha = 0.0f;

	// Declare a variable to track whether the zoom is active
	bool bIsZooming = false;
};
