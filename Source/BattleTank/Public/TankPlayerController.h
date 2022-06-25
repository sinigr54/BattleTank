// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();

	void SetPawn(APawn* InPawn) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation{0.5f};

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation{0.33333f};

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange{1000000.0f};

	UTankAimingComponent* TankAimingComponent{nullptr};

	void BeginPlay() override;

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

	UFUNCTION()
	void OnTankDeath();
};
