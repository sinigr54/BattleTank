// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;

class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn {
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Firing")
    float LaunchSpeed{100000.0f}; // 1000 m / s

    // Sets default values for this pawn's properties
    ATank();

    void AimAt(const FVector &hitLocation);

    UFUNCTION(BlueprintCallable, Category = "Setup")

    void SetBarrel(UTankBarrel *barrel);

protected:

    UTankAimingComponent *tankAimingComponent{nullptr};

    // Called when the game starts or when spawned
    void BeginPlay() override;

public:
    // Called every frame
    void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

};
