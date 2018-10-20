// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include <Engine/World.h>

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    ControlledTank = GetPawn();
    PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (ensure(PlayerTank != nullptr && TankAimingComponent != nullptr)) {
        // Move towards the player
        MoveToActor(PlayerTank, AcceptanceRadius);

        // Aim at the player
        TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

        // Fire if ready
//        ControlledTank->Fire();
    }
}
