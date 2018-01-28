// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// No Need to protect ppointers as added at constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimComponent"));

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame


void ATank::AimAt(FVector HitLocation)
{

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

