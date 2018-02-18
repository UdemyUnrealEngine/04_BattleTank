// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"





void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	Aimingcomponenet = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  
	
	auto PlayerController = (GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerController) {
		MoveToActor(PlayerController, MoveToRange);
		
		if (Aimingcomponenet->AimAt( PlayerController->GetActorLocation() ) ) {
			Aimingcomponenet->Fire();
		}
		
		
			
		
	}
		

}
void ATankAIController::AimAt(FVector HitLocation)
{
}

