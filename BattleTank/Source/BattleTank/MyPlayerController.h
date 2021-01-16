// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Setup")
	ATank* GetControlledTank() const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	UFUNCTION()
	void StartSoectatingOnly();

	virtual void SetPawn(APawn* InPawn) override;

	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	// Start the tank moving the barrel so that a shot would it where 
	// the crosshair intersections
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector&) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;


	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
