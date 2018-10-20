// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include <Engine/World.h>

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    ControlledTank = Cast<ATank>(GetPawn());

    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    PlayerTank = PlayerPawn != nullptr ? Cast<ATank>(PlayerPawn) : nullptr;
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (ensure(PlayerTank != nullptr)) {
        // Move towards the player
        MoveToActor(PlayerTank, AcceptanceRadius);

        // Aim at the player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        // Fire if ready
        ControlledTank->Fire();
    }
}
