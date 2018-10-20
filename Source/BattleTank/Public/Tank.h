// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

protected:
    // Called when the game starts or when spawned
    void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed{4000.0f}; // 4 m / s

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds{3};

    double LastFireTime{0};

    const FString TAG{"ATank"};

    // Sets default values for this pawn's properties
    ATank();

};
