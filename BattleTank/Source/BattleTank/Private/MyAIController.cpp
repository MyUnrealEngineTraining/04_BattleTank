// Fill out your copyright notice in the Description page of Project Settings.
#include "MyAIController.h"
#include "Tank.h"


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
		if (!ensure(PossessedTank)) { return;}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AMyAIController::OnPossedTankDeath);
	}
}

void AMyAIController::OnPossedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank died DELEGATE"));
}