// Fill out your copyright notice in the Description page of Project Settings.

#include <BattleTank/Public/Projectile.h>

#include "BattleTank/Public/Projectile.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = static_cast<uint8>(false);

    CollisionMesh =
            CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(false);

    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
    LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
    ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->SetAutoActivate(false);

    ProjectileMovementComponent =
            CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
    Super::BeginPlay();

    OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed) {
    if (ensure(ProjectileMovementComponent != nullptr)) {
        ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
        ProjectileMovementComponent->Activate();
    }
}

void AProjectile::OnHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult &Hit) {
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
}


