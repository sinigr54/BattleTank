// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/Public/TankMovementComponent.h"
#include "BattleTank/Public/TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrack, UTankTrack *RightTrack) {
    this->LeftTrack = LeftTrack;
    this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
    if (ensure(LeftTrack != nullptr && RightTrack != nullptr)) {
        LeftTrack->SetThrottle(Throw);
        RightTrack->SetThrottle(Throw);
    }
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
    if (ensure(LeftTrack != nullptr && RightTrack != nullptr)) {
        LeftTrack->SetThrottle(Throw);
        RightTrack->SetThrottle(-Throw);
    }
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) {
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    auto DotProduct = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(DotProduct);

    auto CrossProduct = FVector::CrossProduct(TankForward, AIForwardIntention);
    IntendTurnRight(CrossProduct.Z);
}
