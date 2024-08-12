// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponentRife.generated.h"

class AShootToKillPlayerCharacter;
class AShootToKillEnemyRiflemenCharacter;
class ASTKSquadLeaderCharacter;


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTOKILL_API UWeaponComponentRife : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AShootToKillProjectile> ProjectileClass;

	// Attaches the Rifle to the player character
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachRifle(AShootToKillPlayerCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PutAwayRifle();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullOutRifle();

	// Attaches the weapon to the Ai
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeaponToAi(AShootToKillEnemyRiflemenCharacter* TargetCharacter);

	// Attaches the weapon to ai squad leader characters.
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeaponToSquadLeader(ASTKSquadLeaderCharacter* TargetCharacter);

	// Makes the gun fire
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	// Makes Ai Riflemen fire the gun
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AiFire();

	// Makes Ai SquadLeader fire the gun
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AiSquadLeaderFire();

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

	UWeaponComponentRife();

private:

	// The character holding the weapon
	AShootToKillPlayerCharacter* PlayerCharacter;

	// Enemy riflemen ref
	AShootToKillEnemyRiflemenCharacter* RiflemenCharacter;

	// Sqaud Leader ref.
	ASTKSquadLeaderCharacter* SquadLeaderCharacter;

protected:
	// Ends gameplay for this component
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
