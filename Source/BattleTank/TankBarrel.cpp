// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float relativeSpeed) {
    // Rotate barrel then right amount this frame
    // Given a max elevation speed, and the frame time
    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
    if (FMath::Abs(relativeSpeed) < RELATIVE_SPEED_EPSILON) {
        return;
    }

    auto elevationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
    auto elevation = FMath::Clamp(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);

    SetRelativeRotation(FRotator(elevation, 0, 0));
}
