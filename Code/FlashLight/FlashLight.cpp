// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#include "FlashLight.h"
#include "FPSPlayer.h"

#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AFlashLight::AFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);
}

void AFlashLight::ToggleFlashlight()
{
	SpotLight->ToggleVisibility();
}

void AFlashLight::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn && PlayerPawn->IsA<AFPSPlayer>())
	{
		AFPSPlayer* PlayerCharacter = Cast<AFPSPlayer>(PlayerPawn);
		if (PlayerCharacter)
		{
			AttachToComponent(PlayerCharacter->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}

void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn && PlayerPawn->IsLocallyControlled())
	{
		APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->GetController());
		if (PlayerController)
		{
			FVector CameraLocation;
			FRotator CameraRotation;
			PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

			// Update the spotlight's rotation to match the camera's rotation
			SpotLight->SetWorldRotation(CameraRotation);
			SpotLight->SetIntensity(52830);
		}
	}
}
