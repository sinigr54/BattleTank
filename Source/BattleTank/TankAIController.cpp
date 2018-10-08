// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"

#include <Engine/World.h>

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    auto playerTank = GetPlayerTank();
    if (playerTank != nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("AIController found player %s"), *playerTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Player tank not possessed"));
    }
}

ATank *ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerTank() const {
    auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    return playerPawn != nullptr ? Cast<ATank>(playerPawn) : nullptr;
}
