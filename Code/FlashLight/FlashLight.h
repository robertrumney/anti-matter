// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlashLight.generated.h"

class USpotLightComponent;
class UStaticMeshComponent;

UCLASS()
class ANTIMATTERGAME_API AFlashLight : public AActor
{
	GENERATED_BODY()

public:
	AFlashLight();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpotLightComponent* SpotLight;

	virtual void ToggleFlashlight();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
