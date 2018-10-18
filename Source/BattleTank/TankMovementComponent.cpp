// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrack, UTankTrack *RightTrack) {
    if (LeftTrack == nullptr || RightTrack == nullptr) {
        return;
    }

    this->LeftTrack = LeftTrack;
    this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) {
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    auto DotProduct = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(DotProduct);

    auto CrossProduct = FVector::CrossProduct(TankForward, AIForwardIntention);
    IntendTurnRight(CrossProduct.Z);
}
