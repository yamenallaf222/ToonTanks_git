// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh); 
}

void ABasePawn::HandleDestruction()
{
	//TODO : Handle GFX and SFX of Death of the pawn 
	if(DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	if (DeathCameraShakeClass)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);

}

void  ABasePawn::RotateTurret(FVector LookAtTarget)
{

		FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
		FRotator ToTargetRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
		
		if (TurretMesh)
			TurretMesh->SetWorldRotation(ToTargetRotation);



}

void ABasePawn::Fire() 
{
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 50.f, 12, FColor::Red, 0 , 3.f);

	AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	NewProjectile->SetOwner(this);

}