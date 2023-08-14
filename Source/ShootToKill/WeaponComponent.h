// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

class AShootToKillPlayerCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTOKILL_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AShootToKillProjectile> ProjectileClass;

	// Attaches the weapon to the player character
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(AShootToKillPlayerCharacter* TargetCharacter);

	// Makes the gun fire
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SemiAutoFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FullAutoFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopFullAutoFire();

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
	class UInputAction* SemiAutoFireAction;

	// Adds Full-Auto fire input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivate = "true"))
	class UInputAction* FullAutoFireAction;

	UWeaponComponent();

private:

	// The character holding the weapon
	AShootToKillPlayerCharacter* PlayerCharacter;

	bool IsBeingHolded = false;

protected:
	// Ends gameplay for this component
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
