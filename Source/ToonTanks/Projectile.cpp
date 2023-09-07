// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	SmokeTrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeTrailParticles"));

	SmokeTrailParticles->SetupAttachment(RootComponent);


	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	
	ProjectileMovementComponent->InitialSpeed = 10.f;

	ProjectileMovementComponent->MaxSpeed = 100.f;



	



}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if(LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();

	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	UClass* DamageTypeClass = UDamageType::StaticClass();
	
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if (HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		if (HitSound)
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

		if (HitCameraShakeClass)
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);


			
	}
	
	Destroy();
}


