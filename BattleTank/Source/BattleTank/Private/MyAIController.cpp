// Fill out your copyright notice in the Description page of Project Settings.
#include "MyAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (TankAimingComponent->GetFiringState() == EFiringState::Locked) 
	{
		TankAimingComponent->Fire();
	}
}

void AMyAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return;}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AMyAIController::OnPossedTankDeath);
	}
}

void AMyAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())) {

	}
	UE_LOG(LogTemp, Warning, TEXT("Tank died DELEGATE"));
	GetPawn()->DetachFromControllerPendingDestroy();
}