// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
void UTankTrack::SetSpeed(float speed)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, speed);
	auto ForceApplied = GetForwardVector() * speed * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto Tankroot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent() );
	Tankroot->AddForceAtLocation(ForceApplied, ForceLocation);
	
}
