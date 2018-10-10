// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float relativeSpeed) {
    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
    if (FMath::Abs(relativeSpeed) < RELATIVE_SPEED_EPSILON) {
        return;
    }

    auto rotationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto newRotation = RelativeRotation.Yaw + rotationChange;

    SetRelativeRotation(FRotator(0, newRotation, 0));
}
