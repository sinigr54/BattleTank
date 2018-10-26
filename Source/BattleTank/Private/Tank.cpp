// Fill out your copyright notice in the Description page of Project Settings.

#include <BattleTank/Public/Tank.h>

#include "Tank.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator,
                        AActor *DamageCauser) {

    int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
    int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

    CurrentHealth -= DamageToApply;
    if (CurrentHealth <= 0) {
        UE_LOG(LogTemp, Warning, TEXT("%s: Died"), *GetName());
    }

    return DamageToApply;
}

float ATank::GetHealthPercent() const {
    return static_cast<float>(CurrentHealth) / static_cast<float>(DefaultHealth);
}
