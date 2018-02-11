// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"
/**
 * 
 */
class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))


class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntentMoveForward(float speed);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntentMoveBack(float speed);
	
	//UFUNCTION(BlueprintCallable, Category = Input)
	//void IntentBreak(float speed);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntentMoveRight(float speed);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntentMoveLeft(float speed);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTrackRefrense(UTankTrack *LeftTrack, UTankTrack *RightTrack);

private:
	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;
};
