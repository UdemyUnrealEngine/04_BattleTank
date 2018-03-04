// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

class UTankAimingComponent;


UCLASS()

class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	
	// so we can override the function in blueprint,or use BlueprintNativeEvent if you whant both c++ and blueprint implementation
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent * AimcopRef);
	virtual void SetPawn(APawn *inPawn) override;
	UFUNCTION(BlueprintCallable)
	void AimTowardsCrosshair();
private:
	
	UFUNCTION()
	void OnDeath();
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetRayCastLocation(FVector,FVector& HitLocation) const;
	bool GetLookDirection(FVector2D CrosshairLocatin,FVector &LookDirection) const ;
	UTankAimingComponent * Aimingcomponenet = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 8000;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 100000.0;
};
