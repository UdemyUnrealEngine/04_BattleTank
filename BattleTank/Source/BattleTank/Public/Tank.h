// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel * BarrelToSet);
	UTankBarrel * GetBarrelReference() const;
	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret * TurretToSet);
private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	// Sesible starting value of 1000 m/s
	float LaunchSpeed = 4000; 
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTImeInSecounds = 3;
	float LastFireTime = 0;
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile>  ProjectileBlueprint ; // alternetive https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/
	// local refrense to the barrel to spawn projectiles.
	UTankBarrel * Barrel = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent * TankAimingComponent = nullptr;
	

public:	
	// Called every frame
	
	bool AimAt(FVector HitLocation);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
