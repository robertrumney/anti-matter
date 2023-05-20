#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "AFPSCharacter.generated.h"

UCLASS()
class ANTIMATTERGAME_API AAFPSCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Toggle the torch on/off
	void ToggleTorch();

private:
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere)
		USpotLightComponent* Torch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
		float Sanity;

	bool bIsTorchOn;
};
