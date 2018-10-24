// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/Projectile.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    ProjectileMovementComponent =
            CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
    ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
    Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed) {
    if (ensure(ProjectileMovementComponent != nullptr)) {
        ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
        ProjectileMovementComponent->Activate();
    }
}
