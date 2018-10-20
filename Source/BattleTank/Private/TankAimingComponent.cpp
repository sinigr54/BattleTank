// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
    UActorComponent::BeginPlay();

    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                         FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
        FiringStatus = EFiringStatus::Reloading;
    } else if (IsBarrelMoving()) {
        FiringStatus = EFiringStatus::Aiming;
    } else {
        FiringStatus = EFiringStatus::Locked;
    }
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {
    UTankAimingComponent::Barrel = BarrelToSet;
    UTankAimingComponent::Turret = TurretToSet;
}

void UTankAimingComponent::Fire() {
    if (ensure(ProjectileBlueprint.Get() != nullptr)) {
        if (FiringStatus == EFiringStatus::Locked) {
            auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                    ProjectileBlueprint,
                    Barrel->GetSocketLocation(FName("Projectile")),
                    Barrel->GetSocketRotation(FName("Projectile"))
            );

            Projectile->LaunchProjectile(LaunchSpeed);

            LastFireTime = FPlatformTime::Seconds();
        }
    }
}

void UTankAimingComponent::AimAt(const FVector &WorldSpaceAim) {
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
            AimDirection = OutLaunchVelocity.GetSafeNormal();

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

bool UTankAimingComponent::IsBarrelMoving() const {
    return FMath::Abs(AimDirection.Rotation().Yaw - Barrel->GetForwardVector().Rotation().Yaw) > 0.5f;
}
