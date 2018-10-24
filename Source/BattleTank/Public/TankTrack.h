// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);

    void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce{40000000.0f};

    float CurrentThrottle{0};

    UTankTrack();

    UFUNCTION()
    void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
               FVector NormalImpulse,
               const FHitResult &Hit);

    void ApplySidewaysForce();

    void DriveTrack();
};
