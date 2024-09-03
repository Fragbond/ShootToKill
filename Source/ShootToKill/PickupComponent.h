// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ShootToKillPlayerCharacter.h"
#include "ShootToKillEnemyRiflemenCharacter.h"
#include "STKSquadLeaderCharacter.h"
#include "STKSniper.h"
#include "PickupComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AShootToKillPlayerCharacter*, PickupCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAiOnPickUp, AShootToKillEnemyRiflemenCharacter*, AiPickupCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSquadLeaderPickup, ASTKSquadLeaderCharacter*, SquadLeaderCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSniperPickup, ASTKSniper*, SniperCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTOKILL_API UPickupComponent : public USphereComponent
{
	GENERATED_BODY()
	
	// The character holding the weapon
	AShootToKillPlayerCharacter* PlayerCharacter;

public:

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickup;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FAiOnPickUp OnAiPickup;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnSquadLeaderPickup OnSquadLeaderPickup;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnSniperPickup OnSniperPickup;

	UPickupComponent();
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
