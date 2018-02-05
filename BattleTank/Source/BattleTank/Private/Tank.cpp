// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// No Need to protect ppointers as added at constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimComponent"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MoveComponent"));
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);

	//used for spawning projectiles
	Barrel = BarrelToSet;
}
UTankBarrel * ATank::GetBarrelReference() const
{

	return Barrel;
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
void ATank::SetTurretReference(UTankTurret * TurretToSet) {

	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::SetTrackRefrense(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	TankMovementComponent->SetTrackRefrense(LeftTrackToSet, RightTrackToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame


bool ATank::AimAt(FVector HitLocation)
{

	if (TankAimingComponent->AimAt(HitLocation, LaunchSpeed)) {
		return true;
	}
	return false;
}

void ATank::MoveForward(float speed)
{
	TankMovementComponent->IntentMoveForward(speed);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

