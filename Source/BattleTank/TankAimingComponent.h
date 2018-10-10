// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANK_API UTankAimingComponent : public UActorComponent {
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UTankAimingComponent();

    void AimAt(const FVector &worldSpaceAim, float launchSpeed);

    void SetBarrel(UTankBarrel *barrel);

private:

    UTankBarrel *barrel{nullptr};

    void MoveBarrelTowards(const FVector &aimDirection);
};