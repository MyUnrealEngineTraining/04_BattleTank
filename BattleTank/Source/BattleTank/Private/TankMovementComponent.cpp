// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankFroward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention= MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankFroward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	auto RightThrow = FVector::CrossProduct(TankFroward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring  to %s"), *TankName, *MoveVelocityString)
}

void UTankMovementComponent::IntendMoveForward(float Intend)
{
	if (!LeftTrack || !RightTrack) { return; }
	Intend = FMath::Clamp<float>(Intend, -1, 1);
	LeftTrack->SetThrottle(Intend);
	RightTrack->SetThrottle(Intend);
}

void UTankMovementComponent::IntendTurnRight(float Intend)
{
	if (!LeftTrack || !RightTrack) { return; }
	Intend = FMath::Clamp<float>(Intend, -1, 1);
	LeftTrack->SetThrottle(Intend);
	RightTrack->SetThrottle(-Intend);
}

