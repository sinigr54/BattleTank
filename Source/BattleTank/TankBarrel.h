// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds barrel properties and Elevate method
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent {
    GENERATED_BODY()

public:

    void Elevate(float RelativeSpeed);

private:

    const float RELATIVE_SPEED_EPSILON{0.005f};

    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaxDegreesPerSecond{10.0f};

    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaxElevationDegrees{40.0f};

    UPROPERTY(EditAnywhere, Category = "Setup")
    float MinElevationDegrees{0.0f};
};
