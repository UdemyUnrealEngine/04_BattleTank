// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankBarrel.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"



ATankAIController::ATankAIController(const FObjectInitializer & ObjectInitializer) {
	
	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	PrimaryActorTick.bCanEverTick = true;
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossesedTank = Cast<ATank>(InPawn);
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnDeath);
		
	}
	
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	Aimingcomponenet = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	PlayerController = (GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

void ATankAIController::OnDeath()
{
	if (!GetPawn()) { return; };
	GetPawn()->DetachFromControllerPendingDestroy();

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  
	
	
	if (PlayerController) {
		MoveToActor(PlayerController, MoveToRange);
		
		if (Aimingcomponenet->AimAt( PlayerController->GetActorLocation() ) ) {
			Aimingcomponenet->Fire();
		}
		
	}
		
}


