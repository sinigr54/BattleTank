// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * Holds turret properties and Rotate method
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANK_API UTankTurret : public UStaticMeshComponent {
    GENERATED_BODY()

public:

    inline void Rotate(float relativeSpeed);

private:

    const float RELATIVE_SPEED_EPSILON{0.005f};

    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaxDegreesPerSecond{20.0f};

    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaxRotationDegrees{178.0f};

    UPROPERTY(EditAnywhere, Category = "Setup")
    float MinRotationDegrees{-178.0f};
};
