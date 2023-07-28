// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ShootToKillPlayerCharacter.h"
#include "PickupWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AShootToKillPlayerCharacter*, PickupCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTOKILL_API UPickupWeaponComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickup;

	UPickupWeaponComponent();
protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
