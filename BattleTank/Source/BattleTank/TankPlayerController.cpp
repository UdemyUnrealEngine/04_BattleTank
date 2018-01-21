// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	ATank* Tank = GetcontrolledTank();
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("%s was found"),*Tank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ControlledTank pawn not returned"));
	}
}

ATank* ATankPlayerController::GetcontrolledTank() const {
	return Cast<ATank>(GetPawn());
}
