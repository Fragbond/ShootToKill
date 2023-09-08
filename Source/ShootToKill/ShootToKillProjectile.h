// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootToKillProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class AShootToKillPlayerCharacter;
class AShootToKillEnemyCharacter;

UCLASS(config=Game)
class SHOOTTOKILL_API AShootToKillProjectile : public AActor
{
	GENERATED_BODY()

	// Adds sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	// Adds projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
public:	
	// Sets default values for this actor's properties
	AShootToKillProjectile();
	
	// Called when projectile hits something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Returns collision component
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	// Returns Projectile movement component
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
};
