// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "MyAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 3000;

private:


	UTankAimingComponent* TankAimingComponent = nullptr;
	virtual void Tick(float) override;
	
};

