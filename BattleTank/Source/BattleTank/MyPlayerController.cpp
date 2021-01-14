// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"



void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (ensure(tank)) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller possessing %s"), *tank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller no possessing "));
		return;

	}
	auto AimingComponent = tank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void AMyPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }
	
	FVector HitLocation = FVector(0);
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool AMyPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("Deproject: %s"), *LookDirection.ToString()); 
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
//	DrawDebugLine(
//		GetWorld(),
//		GetOwner()->GetActorLocation(),
//		WorldDirection,
//		FColor(255, 0, 0),
//		false,
//		0.0f,
//		0.0f,
//		10.0f
//	);
	return true;
}

bool AMyPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}

bool AMyPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldDirection;
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}


ATank* AMyPlayerController::GetControlledTank() const
{
	return Cast<ATank> (GetPawn());
}


