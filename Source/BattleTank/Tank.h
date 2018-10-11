// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;

class UTankBarrel;

class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Firing")
    float LaunchSpeed{4000.0f}; // 4 m / s

    // Called to bind functionality to input
    void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Firing")

    void Fire();

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetBarrel(UTankBarrel *barrel);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetTurret(UTankTurret *turret);

    void AimAt(const FVector &hitLocation);

protected:
    UTankAimingComponent *tankAimingComponent{nullptr};

    // Called when the game starts or when spawned
    void BeginPlay() override;

private:
    // Sets default values for this pawn's properties
    ATank();

};
