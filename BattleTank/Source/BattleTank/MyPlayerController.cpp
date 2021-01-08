// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (tank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller possessing %s"), *tank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller no possessing "));
		return;

	}
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

}


ATank* AMyPlayerController::GetControlledTank() const
{
	return Cast<ATank> (GetPawn());
}


