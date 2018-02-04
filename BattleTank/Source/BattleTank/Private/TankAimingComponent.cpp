// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Barrel->GetSocketTransform(FName("Barrel")).GetLocation().ToString()
//*Barrel->GetSocketLocation(FName()).ToString()
//auto OwnerName = GetOwner()->GetName();
//UE_LOG(LogTemp, Warning, TEXT("%s is aming at %s from %s "), *OwnerName, *HitLocation.ToString(), *Barrel->GetComponentLocation().ToString())

bool UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed)
{
	if (!Barrel) { return false; } // Barrel is set in blueprint
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
		if (MoveBarrel(AimDirection)) {
			
			return true;
			
		}
	
		//auto time = GetWorld()->GetRealTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim soultion found at %s"), time, *AimDirection.ToString())
	}
	else {

		auto time = GetWorld()->GetRealTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT(" %f: No aim solution found"), time)
	}
	return false;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
	
}



bool UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!Barrel) { return false; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaBarrel = AimDirection.Rotation() - BarrelRotator;
	Barrel->Elevate(DeltaBarrel.Pitch);
	if (!Turret) { return false; }
	if (FMath::Abs(DeltaBarrel.Yaw) < 180)
	{
		Turret->Rotate(DeltaBarrel.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaBarrel.Yaw);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s Got here"), *DeltaBarrel.ToString() )
	if (FMath::Abs(DeltaBarrel.Yaw)< 0.005){
		return true;
	}
	
	return false;
}

