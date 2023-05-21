// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#include "Flashlight.h"
#include "Components/SpotLightComponent.h"

AFlashlight::AFlashlight()
{
	PrimaryActorTick.bCanEverTick = false;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	RootComponent = SpotLight;
}

void AFlashlight::ToggleFlashlight()
{
	SpotLight->ToggleVisibility();
}

void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
	SpotLight->SetVisibility(false);
}
