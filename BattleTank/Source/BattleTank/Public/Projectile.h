// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h" 
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void Launch(float Speed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 1;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Damage = 40;
	
private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	UProjectileMovementComponent * ProjectileMovementComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent * CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent * LanuchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent * InpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent  * Explosion = nullptr;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	
}; 
