// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HAL/CriticalSection.h"
#include "Misc/Optional.h"
#include "DamageComponent.generated.h"

class AShootToKillPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTOKILL_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent(const FObjectInitializer& ObjectIntitializer);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(float BaseDamage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	struct FDamageInfo
	{
		float BaseDamage = 0.0f;
		float AccumulatedTime = 0.0f;
		float CurrentIntervalTime = 0.0f;
		float IntervalTime = 0.0f;
		float Lifetime = 0.0f;
	};

	TOptional<FDamageInfo> ActiveDamageInfo;

	AShootToKillPlayerCharacter* PlayerCharacter = nullptr;

	FCriticalSection CriticalSection;
};
