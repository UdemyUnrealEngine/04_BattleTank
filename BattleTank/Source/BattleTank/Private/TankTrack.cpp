// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"



void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	 
	 ApplySidewaysForce();
	 DriveTrack();
	 CurrentSpeed = 0;
}

UTankTrack::UTankTrack() {
	
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}
void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY tanktrack ticking"))
	
}
void UTankTrack::ApplySidewaysForce()
{
	auto SideForce = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SideForce / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorecctionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorecctionForce);
}
void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentSpeed * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto Tankroot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tankroot->AddForceAtLocation(ForceApplied, ForceLocation);
}
void UTankTrack::SetSpeed(float speed)
{
	
	CurrentSpeed = FMath::Clamp<float>(CurrentSpeed + speed, -1, 1);
	
	
}
