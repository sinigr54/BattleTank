// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
    Super::BeginPlay();
}

void ATank::Fire() {
    /*bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

    if (bIsReloaded) {
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                ProjectileBlueprint,
                TankAimingComponent->GetBarrel()->GetSocketLocation(FName("Projectile")),
                TankAimingComponent->GetBarrel()->GetSocketRotation(FName("Projectile"))
        );

        Projectile->LaunchProjectile(LaunchSpeed);

        LastFireTime = FPlatformTime::Seconds();
    }*/
}
