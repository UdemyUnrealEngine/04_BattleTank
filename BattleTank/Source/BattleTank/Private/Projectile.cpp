// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ParticleDefinitions.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LanuchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LanuchBlast->SetupAttachment(RootComponent);

	InpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Inpact Blast"));
	InpactBlast->SetupAttachment(RootComponent);
	InpactBlast->bAutoActivate = false;

	Explosion = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion"));
	Explosion->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movment"));
	ProjectileMovementComponent->bAutoActivate = false;
	
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	
}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	LanuchBlast->Deactivate();
	InpactBlast->Activate();
	Explosion->FireImpulse();
	SetRootComponent(InpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(), Explosion->Radius, UDamageType::StaticClass(),TArray<AActor *>());
	FTimerHandle Handel;
	SetLifeSpan(DestroyDelay);

	//how to use Timer and lambda exp
	//GetWorld()->GetTimerManager().SetTimer(Handel, [this]() {Destroy(); }, DestroyDelay, true);
}

void AProjectile::Launch(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}


