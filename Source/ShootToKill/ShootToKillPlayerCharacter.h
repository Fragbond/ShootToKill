// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShootToKillPlayerCharacter.generated.h"

class UCameraComponent;
class UDamageComponent;
class UHealthComponent;
class UInputComponent;
class UAnimMontage;
class USoundBase;
class USkeletalMeshComponent;

UCLASS()
class SHOOTTOKILL_API AShootToKillPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	// Adds player camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCameraComponent;

	// Input mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// Move input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Jump input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UFUNCTION(BlueprintCallable)
	void IsAlive();

public:
	// Sets default values for this character's properties
	AShootToKillPlayerCharacter();

	UCameraComponent* GetPlayerCharacterCameraComponent() const { return PlayerCameraComponent; }

	// Look input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void PickupRifeAmmo();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

	// Adds movement input
	void Move(const FInputActionValue& Value);

	// Adds look input
	void Look(const FInputActionValue& Value);

	FTimerHandle RestartLevelTimerHandle;

	UPROPERTY(EditAnywhere)
	float TimeRestartLevelAfterDeath = 2.0f;

	UFUNCTION()
	void OnDeathTimerFinished();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int RifeAmmo;

	int Hitpoints = 100;

	USkeletalMeshComponent* GetMesh() const { return Mesh; }
};
