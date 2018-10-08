// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"

#include <Engine/World.h>

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    auto controllingTank = GetControllingTank();
    if (controllingTank != nullptr) {
        FString objectPosition = controllingTank->GetActorLocation().ToString();
        UE_LOG(LogTemp, Warning, TEXT("AI controlling tank is at: %s"), *objectPosition);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank"));
    }

    auto playerTank = GetPlayerTank();
    if (playerTank != nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("AIController found player %s"), *playerTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Player tank not possessed"));
    }
}

ATank *ATankAIController::GetControllingTank() const {
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerTank() const {
    auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    return playerPawn != nullptr ? Cast<ATank>(playerPawn) : nullptr;
}
