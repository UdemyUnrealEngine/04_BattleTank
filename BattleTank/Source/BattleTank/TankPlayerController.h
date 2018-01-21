// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void AimTowardsCrosshair();
	
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetRayCastLocation(FVector,FVector& HitLocation) const;
	bool GetLookDirection(FVector2D CrosshairLocatin,FVector &LookDirection) const ;
	ATank * GetcontrolledTank() const;
	
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0;
};
