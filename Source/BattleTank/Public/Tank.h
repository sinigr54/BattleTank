// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn {
    GENERATED_BODY()

public:
    float TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator,
                     AActor *DamageCauser) override;

private:
    // Sets default values for this pawn's properties
    ATank();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 DefaultHealth{100};

    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth{DefaultHealth};
};
