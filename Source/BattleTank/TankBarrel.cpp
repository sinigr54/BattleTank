// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed) {
    // Rotate barrel then right amount this frame
    UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called with speed %f"), relativeSpeed);

    // Given a max elevation speed, and the frame time

}
