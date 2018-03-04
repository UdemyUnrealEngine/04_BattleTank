// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"





// Sets default values
ATank::ATank()
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//auto name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY %s Tank Counstructor"),*name)
	
}






float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth) + .5f;
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("DONKEY %i health"), CurrentHealth)
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
		
		SetLifeSpan(10.f);
	}
	
	return DamageToApply;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	CurrentHealth = StartingHealth;
	Super::BeginPlay();
}

// Called every fram

float ATank::GetHealtPercent() const {
	return (float)CurrentHealth / (float)StartingHealth;
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

