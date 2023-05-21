// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

UCLASS()
class ANTIMATTERGAME_API AFlashlight : public AActor
{
	GENERATED_BODY()

public:
	AFlashlight();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
		class USpotLightComponent* SpotLight;

	void ToggleFlashlight();

protected:
	virtual void BeginPlay() override;
};
