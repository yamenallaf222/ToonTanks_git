// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	void HandleDestruction();
private:
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components" , meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles; 

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
	


	

};
