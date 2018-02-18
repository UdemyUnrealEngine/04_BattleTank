// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetSpeed(float speed);
protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.0;
	UTankTrack();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ApplySidewaysForce();
	void DriveTrack();
	float CurrentSpeed = 0;
};
