// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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
	float AcceptanceRadius = 3000;

private:

	virtual void Tick(float) override;
	
};

