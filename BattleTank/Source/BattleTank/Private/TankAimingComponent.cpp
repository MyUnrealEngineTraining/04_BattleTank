// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentAmmo > 0) {
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSecond)
		{
			FiringState = EFiringState::Reloading;
		}
		else if (IsBarrelMoving()){
			FiringState = EFiringState::Aiming;
		}
		else {
			FiringState = EFiringState::Locked;
		}
	}
	else {
		FiringState = EFiringState::Empty;
	}


}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	CurrentAmmo = CountAmmo;

}

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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards()
{
	//UE_LOG(LogTemp, Warning, TEXT("test %s"), *AimDirection.ToString())
	if (!ensure(Barrel && Turret)) { return; }
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaRotator.Pitch);
	auto DegreesRotate = (DeltaRotator.Yaw > -180.0 && DeltaRotator.Yaw < 180.0) ? DeltaRotator.Yaw : -(DeltaRotator.Yaw / abs(DeltaRotator.Yaw)) * (360.0 - DeltaRotator.Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("orig %f, change %f"), DeltaRotator.Yaw, DegreesRotate)
	Turret->Rotate(DegreesRotate);
	
	
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	//FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")->GetForwardVector());
	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, TowardTurnAccuracy);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }

		FVector locate = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator rotate = Barrel->GetSocketRotation(FName("Projectile"));
		AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, locate, rotate);
		if (!ensure(Projectile)) {
			UE_LOG(LogTemp, Warning, TEXT("SpawnActor recive null point a Projectile"));
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		CurrentAmmo--;
	}



}	

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

//UE_LOG(LogTemp, Warning, TEXT("fire call"));
