// Copyright 2023 Robert Rumney Unreal Engine C++ 48 Hour Game-Jam

#include "FlashLight.h"
#include "FPSPlayer.h"

#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/SoftObjectPtr.h"

AFlashLight::AFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);

	// Folder path of the mesh asset in the Content Browser
	FString MeshFolderPath = "/AntiMatterGame/Content/SketchFab-Models/Torch/textures/"; 

	// Name of the mesh asset file (without extension)
	FString MeshAssetName = "model__1__midComb_light_bottom";

	// Construct the full asset reference path
	FString MeshAssetPath = MeshFolderPath + MeshAssetName;

	// Create a Soft Object Ptr using the asset reference path
	FSoftObjectPath SoftObjectPath(MeshAssetPath);

	// Resolve the Soft Object Ptr to get the actual mesh object
	UStaticMesh* MeshAsset = Cast<UStaticMesh>(SoftObjectPath.ResolveObject());

	FlashLightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashlightMesh"));
	FlashLightMesh->SetupAttachment(RootComponent);
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

	// Set the relative location and rotation of the flashlight mesh
	FlashLightMesh->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));
	FlashLightMesh->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
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
