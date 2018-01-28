// Fill out your copyright notice in the Description page of Project Settings.

#include "tank.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


void ATankPlayerController::BeginPlay() {
	
	Super::BeginPlay();
	
	ATank* Tank = GetcontrolledTank();
	if (Tank) {
		
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ControlledTank pawn not returned"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call parent class tick function  
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	bool bFoundPlayerController = GetcontrolledTank();
	if (!bFoundPlayerController) { return; }

	FVector HitLocation(-1); //OUT param

	bool bFoundHitLocation = GetSightRayHitLocation(HitLocation);
	if (bFoundHitLocation) {
		
		GetcontrolledTank()->AimAt(HitLocation);
		//turn turret
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{

	int32 XViewPort, YViewPort;
	GetViewportSize(XViewPort, YViewPort);
	FVector2D CrossHairLocation(XViewPort * CrossHairXLocation, YViewPort * CrossHairYLocation);
	FVector CrossHairHitDirection;// used as OUT params in GetLookDirection()

	if (GetLookDirection(CrossHairLocation, CrossHairHitDirection)) {//returns a value for CrossHairHitlocation

		return GetRayCastLocation(CrossHairHitDirection, HitLocation);// raycast to trace location and return vector to HitLocation
	
	}
	return false;
	

	
	
	
	
}

bool ATankPlayerController::GetLookDirection(FVector2D CrossHairLocation, FVector & CrossHairHitDirection) const
{
	FVector CameraWorldLocation;// Not Used but needed(OUT param)
	//turns 2d screen posistion in to 3d posistion and direction, last to params ar OUT params
	return DeprojectScreenPositionToWorld(CrossHairLocation.X, CrossHairLocation.Y, CameraWorldLocation, CrossHairHitDirection);


}
bool ATankPlayerController::GetRayCastLocation(FVector CrossHairHitDirection, FVector & HitLocation) const
{

	FHitResult HitResult;
	auto PlayerLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = PlayerLocation + CrossHairHitDirection * LineTraceRange;

	//DrawDebugLine(GetWorld(),PlayerLocation,EndLocation,FColor(255, 0, 0),false, -1, 0,5);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, PlayerLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}



ATank* ATankPlayerController::GetcontrolledTank() const {
	return Cast<ATank>(GetPawn());
}
