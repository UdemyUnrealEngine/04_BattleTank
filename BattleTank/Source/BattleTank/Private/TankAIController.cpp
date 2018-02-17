// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AIController = Cast<ATank>(GetPawn());
	Aimingcomponenet = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(PlayerController)) { return; }
	

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  
	
	
	if (PlayerController) {
		MoveToActor(PlayerController, MoveToRange);
		
		if (Aimingcomponenet->AimAt( PlayerController->GetActorLocation() ) ) {
			AIController->Fire();
		}
		
		
			
		
	}
		

}
void ATankAIController::AimAt(FVector HitLocation)
{
}

