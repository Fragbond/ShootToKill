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

	// Equip Rifle Action input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipRifleAction;

	// Equip Pistol Action input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipPistolAction;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasPistol;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool IsRifleEquip = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool IsPistolEquip = false;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetHasPistol(bool bNewHasPistol);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetHasPistol();

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void PickupRifeAmmo();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void PickupPistolAmmo();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void PickupSmallHealthPack();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void PickupBigHealthPack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Hitpoints = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int RifeAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PistolAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool HasRifle = false;

	UFUNCTION()
	void OnDeathTimerFinished();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

	// Adds movement input
	void Move(const FInputActionValue& Value);

	// Adds look input
	void Look(const FInputActionValue& Value);

	void EquipRifle(const FInputActionValue& Value);
	void EquipPistol(const FInputActionValue& Value);

	FTimerHandle RestartLevelTimerHandle;

	UPROPERTY(EditAnywhere)
	float TimeRestartLevelAfterDeath = 2.0f;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PlayersRifle;
};
