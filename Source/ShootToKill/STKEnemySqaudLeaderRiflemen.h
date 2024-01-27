// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STKEnemySqaudLeaderRiflemen.generated.h"

class UDamageComponent;
class UHealthComponent;
class UInputComponent;

UCLASS(config = Game)
class SHOOTTOKILL_API ASTKEnemySqaudLeaderRiflemen : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTKEnemySqaudLeaderRiflemen();

	// Creates behavior tree for Ai Sqaud leader
	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;

	// Creates arrays for follow points
	UPROPERTY(EditAnywhere, Category = "FollowPoints", Meta = (MakeEditWidget))
	TArray<FVector> FollowPoints;

	// Creates controller for enemy squad leader
	class ASTKEnemySquadLeaderRiflemenController* ASquadLeaderRiflemenController;

private: 
	TArray<FVector> WorldFollowPoints;

	int CurrentPointsIndex = 3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Hitpoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int RifeAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsDead = false;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void PickupRifeAmmo();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void PickupSmallHealthPack();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void PickupBigHealthPack();
};
