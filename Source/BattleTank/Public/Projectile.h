// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

class UStaticMeshComponent;

class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor {
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AProjectile();

    void LaunchProjectile(float Speed);

protected:
    // Called when the game starts or when spawned
    void BeginPlay() override;

private:
    UProjectileMovementComponent *ProjectileMovementComponent{nullptr};

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent *CollisionMesh{nullptr};

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent *LaunchBlast{nullptr};

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent *ImpactBlast{nullptr};

    UFUNCTION()
    void OnHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
