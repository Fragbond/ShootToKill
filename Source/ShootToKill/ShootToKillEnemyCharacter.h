// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootToKillEnemyCharacter.generated.h"

class UDamageComponent;
class UHealthComponent;

UCLASS()
class SHOOTTOKILL_API AShootToKillEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;

	// Creates damage handler
	UPROPERTY(EditAnywhere)
	UDamageComponent* DamageComponent;

	UFUNCTION(BlueprintCallable)
	const bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	const float GetPlayersCurrentHealth() const;

public:
	// Sets default values for this character's properties
	AShootToKillEnemyCharacter();

	// Take damage component
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "ShootToKill")
	void SetDamage(float BaseDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
