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
NoAmmo,
Reloading

};
class UTankBarrel;
class UTankTurret;
class AProjectile;



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	bool AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	int32 GetAmmo() const;
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetReference(UTankTurret * TurretToSet, UTankBarrel * BarrelToSet);
	
	
	bool MoveBarrel(FVector AimDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	

	UPROPERTY(BluePrintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Aiming;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 8000;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTImeInSecounds = 3;
	float LastFireTime = 0;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 Ammo = 3;
	bool bDoneAiming = false;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile>  ProjectileBlueprint; // alternetive https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/
	
	
 	
};
