// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {
    Reloading,
    Aiming,
    Locked,
    OutOfAmmo
};

class UTankBarrel;

class UTankTurret;

class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent {
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UTankAimingComponent();

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

    UFUNCTION(BlueprintCallable, Category = "Firing")
    int GetRoundsLeft() const;

    void AimAt(const FVector &WorldSpaceAim);

    EFiringStatus GetFiringStatus() const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringStatus FiringStatus{EFiringStatus::Reloading};

    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float LaunchSpeed{4000.0f}; // 4 m / s

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds{3};

    double LastFireTime{0};

    FVector AimLocation;

    UTankBarrel *Barrel{nullptr};

    UTankTurret *Turret{nullptr};

    int RoundsLeft{3};

    void MoveBarrelTowards(const FVector &AimDirection);

    bool IsBarrelMoving() const;

    void SetFiringStatusOutOfAmmoIfNeed();
};
