// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankTrack.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//auto name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY %s Tank Counstructor"),*name)
	
}


void ATank::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTImeInSecounds;
	
	if (Barrel && bIsReloaded) {
		auto Bullet = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Bullet")), Barrel->GetSocketRotation(FName("Bullet")));
		Bullet->Launch(LaunchSpeed);
		bIsReloaded = false;
		LastFireTime = GetWorld()->GetTimeSeconds();
		
	}
	
	
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//auto name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY %s Tank BeginPlay c++"),*name)
}

// Called every fram

bool ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return false; }
	if (TankAimingComponent->AimAt(HitLocation, LaunchSpeed)) {
		return true;
	}
	return false;
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

