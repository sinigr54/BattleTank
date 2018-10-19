// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;

class UTankBarrel;

class UTankTurret;

class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn {
    GENERATED_BODY()

public:
    // Called to bind functionality to input
    void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetBarrel(UTankBarrel *Barrel);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetTurret(UTankTurret *Turret);

    void AimAt(const FVector &HitLocation);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Setup")
    UTankAimingComponent *TankAimingComponent{nullptr};

    // Called when the game starts or when spawned
    void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed{4000.0f}; // 4 m / s

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds{3};

    UTankBarrel *Barrel{nullptr};

    double LastFireTime{0};

    // Sets default values for this pawn's properties
    ATank();

};
