// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController {
    GENERATED_BODY()

protected:
    void BeginPlay() override;

    void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 8000;

    UTankAimingComponent *TankAimingComponent{nullptr};

    APawn *PlayerTank{nullptr};
};
