// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
    GENERATED_BODY()

public:

    void Tick(float DeltaSeconds) override;

    ATank *GetControlledTank() const;

    void AimTowardsCrosshair();

protected:

    void BeginPlay() override;

private:

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation{0.5f};

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation{0.33333f};

    UPROPERTY(EditAnywhere)
    float LineTraceRange{1000000.0f};

    bool GetSightRayHitLocation(FVector &hitLocation) const;

    bool GetLookDirection(const FVector2D &screenLocation, FVector &lookDirection) const;

    bool GetLookVectorHitLocation(const FVector &lookDirection, FVector &hitLocation) const;
};
