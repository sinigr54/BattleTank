// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/TankPlayerController.h"
#include "BattleTank/Public/Tank.h"
#include "BattleTank/Public/TankAimingComponent.h"
#include <Engine/World.h>

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent != nullptr)) {
        FoundAimingComponent(AimingComponent);
    }
}

void ATankPlayerController::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
}

ATank *ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
    if (ensure(GetControlledTank() != nullptr)) {
        FVector HitLocation{0.0f};
        if (GetSightRayHitLocation(HitLocation)) {
            GetControlledTank()->AimAt(HitLocation);
        }
    }
}

/*
 * Get world location of line trace through crosshair, true if hits landscape
 */
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {
    // Find the crosshair position in screen coordinates
    int32 ViewportSizeX;
    int32 ViewportSizeY;

    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation{ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation};

    // "De-project" the scene position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection)) {
        // Line-trace along that look direction, and see what we hit (up to max range)
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D &ScreenLocation, FVector &LookDirection) const {
    FVector WorldLocation; // To be discarded
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector &LookDirection, FVector &HitLocation) const {
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    bool bIsHitSucceeds = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECollisionChannel::ECC_Visibility
    );

    if (bIsHitSucceeds) {
        HitLocation = HitResult.Location;
    }

    return bIsHitSucceeds;
}
