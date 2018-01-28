// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
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

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto OwnerName = GetOwner()->GetName();
	FName BarrelAt;
	UE_LOG(LogTemp, Warning, TEXT("%s is aming at %s from %s "), *OwnerName, *HitLocation.ToString(), *Barrel->GetComponentLocation().ToString())
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
	
	auto OwnerName = GetOwner()->GetName();
	
}

void UTankAimingComponent::GetBarrelReference()
{
	auto OwnerName = GetOwner()->GetName();
	
}

