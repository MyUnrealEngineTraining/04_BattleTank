// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet) || !ensure(RightTrackToSet)) { return; }
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
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	Intend = FMath::Clamp<float>(Intend, -1, 1);
	//UE_LOG(LogTemp, Warning, TEXT("moveforward befor %f"), Intend)
	LeftTrack->SetThrottle(Intend);
	//UE_LOG(LogTemp, Warning, TEXT("moveforward after %f"), Intend)
		RightTrack->SetThrottle(Intend);
}

void UTankMovementComponent::IntendTurnRight(float Intend)
{
	//UE_LOG(LogTemp, Warning, TEXT("move right"))
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	Intend = FMath::Clamp<float>(Intend, -1, 1);
	LeftTrack->SetThrottle(Intend);
	RightTrack->SetThrottle(-Intend);
}

