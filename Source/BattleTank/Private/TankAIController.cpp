// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include <Engine/World.h>
#include "Tank.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (ensure(PlayerTank != nullptr && TankAimingComponent != nullptr)) {
        // Move towards the player
        MoveToActor(PlayerTank, AcceptanceRadius);

        // Aim at the player
        TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

        if (TankAimingComponent->GetFiringStatus() == EFiringStatus::Locked ||
                TankAimingComponent->GetFiringStatus() == EFiringStatus::Aiming) {

            TankAimingComponent->Fire();
        }
    }
}

void ATankAIController::SetPawn(APawn *InPawn) {
    AAIController::SetPawn(InPawn);

    if (InPawn != nullptr) {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (ensure(PossessedTank != nullptr)) {
            PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
        }
    }
}

void ATankAIController::OnTankDeath() {
    if (ensure(GetPawn() != nullptr)) {
        GetPawn()->DetachFromControllerPendingDestroy();
    }
}
