// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "CoreMinimal.h"
#include "Engine/World.h"



void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecounds * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp(RawNewElevation,MinHight, MaxHight);
	SetRelativeRotation(FRotator(Elevation, 0, 0));

	
}