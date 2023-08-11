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

	// Attaches the weapon to the player character
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon(AShootToKillPlayerCharacter* TargetCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UWeaponComponent();

private:

	// The character holding the weapon
	AShootToKillPlayerCharacter* PlayerCharacter;
};
