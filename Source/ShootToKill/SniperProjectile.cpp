// Fill out your copyright notice in the Description page of Project Settings.


#include "SniperProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShootToKillPlayerCharacter.h"
#include "STKSniper.h"
#include "STKSquadLeaderCharacter.h"
#include "ShootToKillEnemyRiflemenCharacter.h"

// Sets default values
ASniperProjectile::ASniperProjectile()
{
	// Creates sphere for the sniper projectile.
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ASniperProjectile::OnHit);
	// Makes is so the player can't walk on the projectile.
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	// Creates the root component.
	RootComponent = CollisionComp;
	// Govern the projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 6000.f;
	ProjectileMovement->MaxSpeed = 6000.f;
}

void ASniperProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASTKSniper* Sniper = Cast<ASTKSniper>(OtherActor);
	ASTKSquadLeaderCharacter* SquadLeader = Cast<ASTKSquadLeaderCharacter>(OtherActor);
	AShootToKillPlayerCharacter* Player = Cast<AShootToKillPlayerCharacter>(OtherActor);
	AShootToKillEnemyRiflemenCharacter* Riflemen = Cast<AShootToKillEnemyRiflemenCharacter>(OtherActor);

	if (OtherActor == Sniper)
	{
		Sniper->Hitpoints = Sniper->Hitpoints - 45;

		Destroy();

		if (Sniper->Hitpoints <= 0)
		{
			Sniper->IsDead = true;
		}
	}
	else if (OtherActor == SquadLeader)
	{
		SquadLeader->Hitpoints = SquadLeader->Hitpoints - 45;

		Destroy();

		if (SquadLeader->Hitpoints <= 0)
		{
			SquadLeader->IsDead = true;
		}
	}
	else if (OtherActor == Riflemen)
	{
		Riflemen->Hitpoints = Riflemen->Hitpoints - 45;

		Destroy();

		if (Riflemen->Hitpoints <= 0)
		{
			Riflemen->IsDead = true;
		}
	}
	else if (OtherActor == Player)
	{
		Destroy();

		if (Player->Hitpoints <= 0)
		{
			Player->OnDeathTimerFinished();
		}
	}
	else if (OtherActor != nullptr)
	{
		Destroy();
	}
}