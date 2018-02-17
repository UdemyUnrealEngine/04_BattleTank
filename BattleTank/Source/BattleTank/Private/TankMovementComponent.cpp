// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Engine/World.h"


void UTankMovementComponent::IntentMoveForward(float speed)
{
	LeftTrack->SetSpeed(speed);
	RightTrack->SetSpeed(speed);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto AITankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIMoveTo = MoveVelocity.GetSafeNormal();
	auto AITankMoveTo = FVector::DotProduct(AITankForward, AIMoveTo);

	auto AITankMOveCross = FVector::CrossProduct(AITankForward, AIMoveTo);
	IntentMoveRight(AITankMOveCross.Z);
	IntentMoveForward(AITankMoveTo);
	//UE_LOG(LogTemp, Warning, TEXT("tank %s whants to move to %s"), *owner, *MoveVelocity.ToString())
}
void UTankMovementComponent::IntentMoveBack(float speed)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetSpeed(speed);
	RightTrack->SetSpeed(speed);
}

void UTankMovementComponent::IntentMoveRight(float speed)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetSpeed(speed);
	RightTrack->SetSpeed(-speed);
}

void UTankMovementComponent::IntentMoveLeft(float speed)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetSpeed(-speed);
	RightTrack->SetSpeed(speed);
}

void UTankMovementComponent::SetTrackRefrense(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
