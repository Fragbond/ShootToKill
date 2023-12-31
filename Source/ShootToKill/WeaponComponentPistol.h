// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponentPistol.generated.h"

class AShootToKillPlayerCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTOKILL_API UWeaponComponentPistol : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AShootToKillProjectile> ProjectileClass;

	// Attaches the Pistol to the player character
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachPistol(AShootToKillPlayerCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PutAwayPistol();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullOutPistol();

	// Attaches the weapon to the player character NOTE: Needs to be added
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//void AttachWeaponToAi(AShootToKillEnemyRiflemenCharacter* TargetCharacter);

	// Makes the gun fire
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	// Makes Ai fire the gun NOTE: Needs to be added
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//void AiFire();

	// Gets guns muzzle location from the characters location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Plays sound when fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	// Adds mapping contexts
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivate = "true"))
	class UInputMappingContext* FireMappingContext;

	// Adds Semi-Auto fire input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivate = "true"))
	class UInputAction* FireAction;

	UWeaponComponentPistol();

private:

	// The character holding the weapon
	AShootToKillPlayerCharacter* PlayerCharacter;

protected:
	// Ends gameplay for this component
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
