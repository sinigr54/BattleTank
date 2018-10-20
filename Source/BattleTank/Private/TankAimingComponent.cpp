// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/TankAimingComponent.h"
#include "BattleTank/Public/TankBarrel.h"
#include "BattleTank/Public/TankTurret.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {
    UTankAimingComponent::Barrel = BarrelToSet;
    UTankAimingComponent::Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(const FVector &WorldSpaceAim, float LaunchSpeed) {
    if (ensure(Barrel != nullptr && Turret != nullptr)) {
        FVector OutLaunchVelocity;
        const FVector &StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

        // Calculate out launch velocity
        bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                this,
                OutLaunchVelocity,
                StartLocation,
                WorldSpaceAim,
                LaunchSpeed,
                false,
                0.0f,
                0.0f,
                ESuggestProjVelocityTraceOption::DoNotTrace
        );

        if (bHaveAimSolution) {
            auto AimDirection = OutLaunchVelocity.GetSafeNormal();

            MoveBarrelTowards(AimDirection);
        }
    }
}

void UTankAimingComponent::MoveBarrelTowards(const FVector &AimDirection) {
    auto AimAsRotator = AimDirection.Rotation();

    // Calculate angle between barrel rotation and aim direction
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto DeltaBarrelRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaBarrelRotator.Pitch);
    if (FMath::Abs(DeltaBarrelRotator.Yaw) < 180) {
        Turret->Rotate(DeltaBarrelRotator.Yaw);
    } else {
        Turret->Rotate(-DeltaBarrelRotator.Yaw);
    }
}

UTankBarrel *UTankAimingComponent::GetBarrel() const {
    return Barrel;
}

UTankTurret *UTankAimingComponent::GetTurret() const {
    return Turret;
}

