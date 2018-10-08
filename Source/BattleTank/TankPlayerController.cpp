// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))

    auto controlledTank = GetControllingTank();
    if (controlledTank == nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
    } else {
        FString objectPosition = controlledTank->GetActorLocation().ToString();
        UE_LOG(LogTemp, Warning, TEXT("Player controlling tank is at: %s"), *objectPosition);
    }
}

ATank *ATankPlayerController::GetControllingTank() const {
    return Cast<ATank>(GetPawn());
}
