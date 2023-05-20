// Copyright 2023 Robert Rumney Unreal Engine 48 Hour Game-Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class ANTIMATTERGAME_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	void OnRightMouseButtonUp();
	void OnRightMouseButtonDown();

	void Turn(float AxisValue);
	void LookUp(float AxisValue);

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

	// Declare a variable to store the lerping alpha
	float LerpingAlpha = 0.0f;

	// Declare a variable to track whether the zoom is active
	bool bIsZooming = false;
};
