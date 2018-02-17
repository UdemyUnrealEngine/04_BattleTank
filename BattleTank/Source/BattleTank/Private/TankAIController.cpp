// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Tank.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AIController = Cast<ATank>(GetPawn());
	if (!ensure(PlayerController)) { return; }
	

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  
	
	
	if (PlayerController) {
		MoveToActor(PlayerController, MoveToRange);
		
		if (AIController->AimAt(PlayerController->GetActorLocation())) {
			//AIController->Fire();
		}
		
		
			
		
	}
		

}
void ATankAIController::AimAt(FVector HitLocation)
{
}

