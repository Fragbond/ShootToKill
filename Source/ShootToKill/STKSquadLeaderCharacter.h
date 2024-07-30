// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STKSquadLeaderCharacter.generated.h"

class UDamageComponent;
class UHealthComponent;
class UInputComponent;

UCLASS(config=Game)
class SHOOTTOKILL_API ASTKSquadLeaderCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTKSquadLeaderCharacter();

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;

	class ASTKSquadLeaderController* STKSquadLeaderController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Hitpoints = 125;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int RifleAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsDead = false;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void PickupSmallHealthPack();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void PickupBigHealthPack();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void PickupRifleAmmo();
};
