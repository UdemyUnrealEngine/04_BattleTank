// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
void UTankTrack::SetSpeed(float speed)
{
	auto Name = GetName();
	
	auto ForceApplied = GetForwardVector() * speed * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto Tankroot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent() );
	Tankroot->AddForceAtLocation(ForceApplied, ForceLocation);
	
}
