// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Rotation"))
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = GetRelativeRotation().Yaw + RotationChange;
	UE_LOG(LogTemp, Warning, TEXT("Rotation %f, RelativeSpeed %f"), RotationChange, Rotation);
	SetRelativeRotation(FRotator(0, Rotation, 0));

}
