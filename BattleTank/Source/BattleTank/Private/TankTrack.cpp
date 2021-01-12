// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("track %s throttle=%f"), *GetName(), Throttle);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	//auto TankRoot = GetOwner()->GetRootComponent();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}