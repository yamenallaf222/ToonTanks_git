// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool bAlive = true;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(float Value);
	void Turn(float Value);
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere ,Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera; 
	
	UPROPERTY(VisibleAnywhere, Category = "Components", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm; 

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Rotation", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float TurnRate = 45.f;

	APlayerController* TankPlayerController;

	

};
