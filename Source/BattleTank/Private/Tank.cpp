// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/Tank.h"
#include "BattleTank/Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "BattleTank/Public/TankBarrel.h"
#include "BattleTank/Public/Projectile.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
    Super::BeginPlay();

    TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(const FVector &HitLocation) {
    if (ensure(TankAimingComponent != nullptr)) {
        TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
    }
}

void ATank::Fire() {
    if (ensure(TankAimingComponent != nullptr)) {
        bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

        if (bIsReloaded) {
            auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                    ProjectileBlueprint,
                    TankAimingComponent->GetBarrel()->GetSocketLocation(FName("Projectile")),
                    TankAimingComponent->GetBarrel()->GetSocketRotation(FName("Projectile"))
            );

            Projectile->LaunchProjectile(LaunchSpeed);

            LastFireTime = FPlatformTime::Seconds();
        }
    }
}
