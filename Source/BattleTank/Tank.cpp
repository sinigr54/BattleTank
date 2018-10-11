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

    tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetBarrel(UTankBarrel *barrel) {
    tankAimingComponent->SetBarrel(barrel);
    ATank::barrel = barrel;
}

void ATank::SetTurret(UTankTurret *turret) {
    tankAimingComponent->SetTurret(turret);
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
    Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(const FVector &hitLocation) {
    tankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

void ATank::Fire() {
    auto time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: Fire"), time);

    GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            barrel->GetSocketLocation(FName("Projectile")),
            barrel->GetSocketRotation(FName("Projectile"))
    );
}
