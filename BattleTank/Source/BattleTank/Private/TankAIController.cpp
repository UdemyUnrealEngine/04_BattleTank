// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"


void ATankAIController::AimAt(FVector HitLocation)
{
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
	

	auto PlayerController = GetPlayerTank();
	if (!PlayerController) {
		UE_LOG(LogTemp, Warning, TEXT("GetPlayerTank function did not find a Player Controller!"))
			
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GetPlayerTank function found %s"), *PlayerController->GetName())
			
	}

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  
	if (GetPlayerTank()) { 
		if (!GetAIControllerPawn()) { return; }
		GetAIControllerPawn()->AimAt(GetPlayerTank()->GetActorLocation());
		

	}
	

	
}
ATank * ATankAIController::GetAIControllerPawn() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	
		ATank* PlayerController = nullptr;
		PlayerController = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
		return PlayerController;
}
