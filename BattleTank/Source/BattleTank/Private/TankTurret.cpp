// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	
		RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
		auto TurnChange = (RelativeSpeed)* MaxDegreesPerSecounds * GetWorld()->GetDeltaSeconds();
		auto RawNewTurn = RelativeRotation.Yaw + TurnChange;
		SetRelativeRotation(FRotator(0, RawNewTurn, 0));
	
	
	

}
