// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h" 
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enums
UENUM()
enum class EFiringStatus :uint8 {
Locked,
Aiming,
Reloading

};
class UTankTurret;
class UTankBarrel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	bool AimAt(FVector HitLocation,float LaunchSpeed);
	void SetBarrelReference(UTankBarrel * BarrelToSet);
	void SetTurretReference(UTankTurret * TurretToSet);
	
	bool MoveBarrel(FVector AimDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BluePrintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	
	
};
