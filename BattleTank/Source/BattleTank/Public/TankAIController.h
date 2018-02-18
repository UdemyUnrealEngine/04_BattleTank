// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly)
	float MoveToRange = 3000;
	
protected:

private:
	
 	virtual void BeginPlay() override;
	ATank * AIController = nullptr;
	UTankAimingComponent * Aimingcomponenet = nullptr;
	
};
