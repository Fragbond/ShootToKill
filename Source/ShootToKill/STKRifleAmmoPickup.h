// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STKRifleAmmoPickup.generated.h"

UCLASS()
class SHOOTTOKILL_API ASTKRifleAmmoPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTKRifleAmmoPickup();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int RifeAmmo = 0;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void PickupRifeAmmo(AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void SetRifeAmmoNum(AActor* OtherActor);
};
