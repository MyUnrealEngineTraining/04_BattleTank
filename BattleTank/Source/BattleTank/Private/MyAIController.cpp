// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		GetControlled()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}
ATank *AMyAIController::GetControlled() const
{
	return Cast<ATank>(GetPawn());
}

ATank* AMyAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	APlayerController *Player = GetWorld()->GetFirstPlayerController();
	if (!PlayerPawn) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not found"));
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	ATank* tank = GetPlayerTank();
	if (tank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller found %s"), *tank->GetName());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not found"));
		return;

	}

}
