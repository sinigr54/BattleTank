// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"

#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetBarrel(UTankBarrel *Barrel) {
    TankAimingComponent->SetBarrel(Barrel);
    ATank::Barrel = Barrel;
}

void ATank::SetTurret(UTankTurret *Turret) {
    TankAimingComponent->SetTurret(Turret);
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
    Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(const FVector &HitLocation) {
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {

    bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

    if (bIsReloaded) {
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                ProjectileBlueprint,
                Barrel->GetSocketLocation(FName("Projectile")),
                Barrel->GetSocketRotation(FName("Projectile"))
        );

        Projectile->LaunchProjectile(LaunchSpeed);

        LastFireTime = FPlatformTime::Seconds();
    }
}
