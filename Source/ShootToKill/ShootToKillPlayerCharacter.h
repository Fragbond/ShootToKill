// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShootToKillPlayerCharacter.generated.h"

class UCameraComponent;
class UDamageHandlerComponent;
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

	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USkeletalMeshComponent* Mesh;

	// Input mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// Move input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Jump input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

	//UPROPERTY(EditAnywhere)
	//UDamageHandlerComponent* DamageHandlerComponent;

	UFUNCTION(BlueprintCallable)
	const bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	const float GetPlayersCurrentHealth() const;

public:
	// Sets default values for this character's properties
	AShootToKillPlayerCharacter();

	UCameraComponent* GetPlayerCharacterCameraComponent() const { return PlayerCameraComponent; }

	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Look input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Adds movement input
	void Move(const FInputActionValue& Value);

	// Adds look input
	void Look(const FInputActionValue& Value);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	USkeletalMeshComponent* GetMesh() const { return Mesh; }
};
