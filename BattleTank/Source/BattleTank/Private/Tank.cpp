// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"





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




// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY %s Tank BeginPlay c++"), *name)
	
	
	Super::BeginPlay();
}

// Called every fram





// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

