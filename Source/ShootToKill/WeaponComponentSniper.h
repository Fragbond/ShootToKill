// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "SniperProjectile.h"
#include "WeaponComponentSniper.generated.h"

class AShootToKillPlayerCharacter;
class ASniperCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTOKILL_API UWeaponComponentSniper : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASniperProjectile> SniperProjectileClass;

	// Attaches the Rifle to the player character
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachSniper(AShootToKillPlayerCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PutAwaySniper();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullOutSniper();

	// Attaches the weapon to the Ai
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeaponToSniper(ASTKSniper* TargetCharacter);

	// Makes the gun fire
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	// Makes Ai Riflemen fire the gun
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SniperFire();

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

	UWeaponComponentSniper();

private:

	// The character holding the weapon
	AShootToKillPlayerCharacter* PlayerCharacter;

	// Sniper character ref.
	ASTKSniper* Sniper;

protected:
	// Ends gameplay for this component
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
