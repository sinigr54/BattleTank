// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetBarrel(UTankBarrel *barrel) {
    UTankAimingComponent::barrel = barrel;
}

void UTankAimingComponent::AimAt(const FVector &worldSpaceAim, float launchSpeed) {
    if (barrel == nullptr) {
        return;
    }

    FVector outLaunchVelocity;
    const FVector &startLocation = barrel->GetSocketLocation(FName("Projectile"));

    // Calculate out launch velocity
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
            this,
            outLaunchVelocity,
            startLocation,
            worldSpaceAim,
            launchSpeed,
            false,
            0.0f,
            0.0f,
            ESuggestProjVelocityTraceOption::DoNotTrace
    );

    if (bHaveAimSolution) {
        auto aimDirection = outLaunchVelocity.GetSafeNormal();

        MoveBarrelTowards(aimDirection);

        auto time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);

    } else {
        auto time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), time);
    }

}

void UTankAimingComponent::MoveBarrelTowards(const FVector &aimDirection) {
    // Calculate angle between barrel rotation and aim direction
    auto barrelRotator = barrel->GetForwardVector().Rotation();
    auto aimAsRotator = aimDirection.Rotation();
    auto deltaRotator = aimAsRotator - barrelRotator;

    barrel->Elevate(deltaRotator.Pitch);
}

