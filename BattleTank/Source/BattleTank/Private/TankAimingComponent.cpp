// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{

	if (!ensure(Barrel && Turret)) { return; }


	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if( bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//UE_LOG(LogTemp, Warning, TEXT("test %s"), *AimDirection.ToString())
	if (!ensure(Barrel && Turret)) { return; }
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
	
	
}

void UTankAimingComponent::Fire()
{

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecond;
	//UE_LOG(LogTemp, Warning, TEXT("fire call"));
	if (!ensure(Barrel)) { return; }
	if (isReloaded)
	{

		FVector locate = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator rotate = Barrel->GetSocketRotation(FName("Projectile"));
		UE_LOG(LogTemp, Warning, TEXT("fire call %s %s"), *locate.ToString(), *rotate.ToString());
		AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, locate, rotate);
		if (!ensure(Projectile)) {
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor recive null point a Projectile"));
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}



}