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
    UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
    UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}
