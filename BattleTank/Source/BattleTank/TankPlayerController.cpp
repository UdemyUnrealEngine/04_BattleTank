// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay() {
	
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	ATank* Tank = GetcontrolledTank();
	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("%s is set to Player Controller"),*Tank->GetName());
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
	if (!GetcontrolledTank()) { return; }
	FVector HitLocation; //OUT param
	if (GetSightRayHitLocation(HitLocation)) {
		
		GetcontrolledTank()->AimAt(HitLocation);
		//turn turret
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{

	int32 XViewPort, YViewPort;
	GetViewportSize(XViewPort, YViewPort);
	FVector2D CrossHairLocation(XViewPort * CrossHairXLocation, YViewPort * CrossHairYLocation);
	FVector CrossHairHitlocation;// used as OUT params in GetLookDirection()

	if (GetLookDirection(CrossHairLocation, CrossHairHitlocation)) {//returns a value for CrossHairHitlocation

		GetRayCastLocation(CrossHairHitlocation, HitLocation);// raycast to trace location and return vector to HitLocation
	
	}
	return true;
	

	
	
	
	
}
bool ATankPlayerController::GetLookDirection(FVector2D CrossHairLocation, FVector & CrossHairHitlocation) const
{
	FVector CameraWorldLocation;// Not Used but needed
	return DeprojectScreenPositionToWorld(CrossHairLocation.X, CrossHairLocation.Y, CameraWorldLocation, CrossHairHitlocation);


}
bool ATankPlayerController::GetRayCastLocation(FVector CrossHairHitlocation, FVector & HitLocation) const
{

	FHitResult HitResult;
	auto PlayerLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = PlayerLocation + CrossHairHitlocation * LineTraceRange;

	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		EndLocation,
		FColor(255, 0, 0),
		false, -1, 0,
		5
	);
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
