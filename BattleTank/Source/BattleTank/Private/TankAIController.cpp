// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Tank.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (!PlayerController) {
		UE_LOG(LogTemp, Warning, TEXT("GetPlayerTank function did not find a Player Controller!"))
			
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("GetPlayerTank function found %s"), *PlayerController->GetName())
			
	}

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  
	PlayerController = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AIController = Cast<ATank>(GetPawn());
	if (AIController && PlayerController) {
		if (AIController->AimAt(PlayerController->GetActorLocation())) {
			AIController->Fire();
		}
		
		
			
		
	}
		

}
void ATankAIController::AimAt(FVector HitLocation)
{
}

