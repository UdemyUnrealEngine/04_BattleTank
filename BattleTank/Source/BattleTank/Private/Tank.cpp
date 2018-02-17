// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankTrack.h"
#include "Engine/World.h"
#include "Projectile.h"




// Sets default values
ATank::ATank()
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY %s Tank Constructor c++"), *name)
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//auto name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY %s Tank Counstructor"),*name)
	
}


void ATank::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTImeInSecounds;
	if ( !ensure(Barrel) ) { return; }
	if (bIsReloaded) {
		auto Bullet = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Bullet")), Barrel->GetSocketRotation(FName("Bullet")));
		Bullet->Launch(LaunchSpeed);
		bIsReloaded = false;
		LastFireTime = GetWorld()->GetTimeSeconds();
		
	}
	
	
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY %s Tank BeginPlay c++"), *name)
	
	Barrel = FindComponentByClass<UTankBarrel>();
	Super::BeginPlay();
}

// Called every fram





// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

