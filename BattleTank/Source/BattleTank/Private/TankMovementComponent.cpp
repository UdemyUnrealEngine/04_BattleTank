// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Engine/World.h"

void UTankMovementComponent::IntentMoveForward(float speed)
{
	LeftTrack->SetSpeed(speed);
	RightTrack->SetSpeed(speed);
}

void UTankMovementComponent::SetTrackRefrense(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
