// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include <Engine/World.h>
#include <BattleTank/Public/TankPlayerController.h>
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(TankAimingComponent != nullptr))
	{
		FoundAimingComponent(TankAimingComponent);
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	APlayerController::SetPawn(InPawn);

	if (InPawn != nullptr)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (ensure(PossessedTank != nullptr))
		{
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
		}
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (ensure(GetPawn() != nullptr && TankAimingComponent != nullptr))
	{
		FVector HitLocation{0.0f};
		if (GetSightRayHitLocation(HitLocation))
		{
			TankAimingComponent->AimAt(HitLocation);
		}
	}
}

/*
 * Get world location of line trace through crosshair, true if hits landscape
 */
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in screen coordinates
	int32 ViewportSizeX;
	int32 ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation{ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation};

	// "De-project" the scene position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	bool bIsHitSucceeds = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams{FName(TEXT("")), false, GetPawn()}
	);

	if (bIsHitSucceeds)
	{
		HitLocation = HitResult.Location;
	}

	return bIsHitSucceeds;
}
