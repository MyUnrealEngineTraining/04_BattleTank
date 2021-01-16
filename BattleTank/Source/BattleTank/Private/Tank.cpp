// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}



float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstagator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrenHealth);
	CurrenHealth -= DamageToApply;
	if (CurrenHealth <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Tank died"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("CurrenHealth %i and DamateToApplay %i"), CurrenHealth, DamageToApply)
	}
	return DamageToApply;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::GetHealthPercent() const
{
	return (float)CurrenHealth / (float)StartingHealth;
}

