// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include <Engine/World.h>

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))

    auto controlledTank = GetControlledTank();
    if (controlledTank == nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
    } else {
        FString objectPosition = controlledTank->GetActorLocation().ToString();
        UE_LOG(LogTemp, Warning, TEXT("Player controlling tank is at: %s"), *objectPosition);
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
    if (!GetControlledTank()) {
        return;
    }

    FVector hitLocation(0.0f);
    if (GetSightHitLocation(hitLocation)) {
        GetControlledTank()->AimAt(hitLocation);
    }
}

/*
 * Get world location of line trace through crosshair, true if hits landscape
 */
bool ATankPlayerController::GetSightHitLocation(FVector &hitLocation) const {
    // Find the crosshair position in screen coordinates
    int32 viewportSizeX;
    int32 viewportSizeY;

    GetViewportSize(viewportSizeX, viewportSizeY);
    FVector2D screenLocation{viewportSizeX * CrossHairXLocation, viewportSizeY * CrossHairYLocation};

    // "De-project" the scene position of the crosshair to a world direction
    FVector lookDirection;
    if (GetLookDirection(screenLocation, lookDirection)) {
        // Line-trace along that look direction, and see what we hit (up to max range)
        GetLookVectorHitLocation(lookDirection, hitLocation);
    }

    return true;
}

bool ATankPlayerController::GetLookDirection(const FVector2D &screenLocation, FVector &lookDirection) const {
    FVector worldLocation; // To be discarded
    return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector &lookDirection, FVector &hitLocation) const {
    FHitResult hitResult;
    auto startLocation = PlayerCameraManager->GetCameraLocation();
    auto endLocation = startLocation + lookDirection * LineTraceRange;

    bool isHitSucceeds = GetWorld()->LineTraceSingleByChannel(
            hitResult,
            startLocation,
            endLocation,
            ECollisionChannel::ECC_Visibility
    );

    if (isHitSucceeds) {
        hitLocation = hitResult.Location;
    }

    return isHitSucceeds;
}
