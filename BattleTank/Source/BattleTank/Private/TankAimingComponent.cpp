// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//Barrel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Barrel"));
	// ...
}
// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Fire()
{
	
	
	if (!ensure(Barrel)) { return; }
	if (FiringStatus != EFiringStatus::Reloading) {
		
		auto Bullet = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Bullet")), Barrel->GetSocketRotation(FName("Bullet")));
		Bullet->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

	}
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	// ...
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTImeInSecounds) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (bDoneAiming) {
		FiringStatus = EFiringStatus::Locked;
	}
	else {
		FiringStatus = EFiringStatus::Aiming;
	}
	// ...
}

// Barrel->GetSocketTransform(FName("Barrel")).GetLocation().ToString()
//*Barrel->GetSocketLocation(FName()).ToString()
//auto OwnerName = GetOwner()->GetName();
//UE_LOG(LogTemp, Warning, TEXT("%s is aming at %s from %s "), *OwnerName, *HitLocation.ToString(), *Barrel->GetComponentLocation().ToString())

bool UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel) ) { return false; } // Barrel is set in blueprint
	FVector OutVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Bullet"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam
	);
	
	if (bHaveAimSolution) {
		
		
		auto AimDirection = OutVelocity.GetSafeNormal();
		bDoneAiming = MoveBarrel(AimDirection);
		if (bDoneAiming) {
			
			return true;
			
		}
	
		//auto time = GetWorld()->GetRealTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim soultion found at %s"), time, *AimDirection.ToString())
	}
	else {
		
		//UE_LOG(LogTemp, Warning, TEXT("No aim solution found"))
	}
	return false;
}



void UTankAimingComponent::SetReference(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



bool UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	
	if (!ensure(Barrel) ) { return false; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaBarrel = AimDirection.Rotation() - BarrelRotator;
	Barrel->Elevate(DeltaBarrel.Pitch);
	if (!ensure(Turret) ) { return false; }
	if (FMath::Abs(DeltaBarrel.Yaw) < 180)
	{
		Turret->Rotate(DeltaBarrel.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaBarrel.Yaw);
	}
	const auto deltavector = AimDirection - Barrel->GetForwardVector();
	
		//FMath::Abs(DeltaBarrel.Yaw)< 0.005
	if (Barrel->GetForwardVector().Equals(AimDirection, 0.007)){
		
		return true;
		
	}
	
	return false;
}

