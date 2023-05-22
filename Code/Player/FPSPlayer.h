// Copyright 2023 Robert Rumney Unreal Engine 48 Hour Game-Jam

#pragma once
#include "FlashLight.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSPlayer.generated.h"

UCLASS()
class ANTIMATTERGAME_API AFPSPlayer : public APawn
{
	GENERATED_BODY()

private:
	AFlashLight* FlashLight;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		bool bHasFlashlight;

	UPROPERTY(EditAnywhere, Category = "Components")
		UCapsuleComponent* CapsuleComponent;

	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void OnRightMouseButtonUp();
	void OnRightMouseButtonDown();
	void PickupFlashLight();
	void BeginSprint();
	void EndSprint();

	//Input variables
	FVector CurrentVelocity;
	bool bGrowing;
	bool bMouseLookEnabled;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed = 4;

	// Inside FPSPlayer.h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float DefaultMovementSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float SprintingMovementSpeed = 6.0f;

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
