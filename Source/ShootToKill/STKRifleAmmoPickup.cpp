// Fill out your copyright notice in the Description page of Project Settings.


#include "STKRifleAmmoPickup.h"
#include "ShootToKillPlayerCharacter.h"
#include "ShootToKillEnemyRiflemenCharacter.h"

// Sets default values
ASTKRifleAmmoPickup::ASTKRifleAmmoPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASTKRifleAmmoPickup::PickupRifeAmmo(AActor* OtherActor)
{
	AShootToKillPlayerCharacter* PlayerCharacter = Cast<AShootToKillPlayerCharacter>(OtherActor);
	AShootToKillEnemyRiflemenCharacter* EnemyCharacter = Cast<AShootToKillEnemyRiflemenCharacter>(OtherActor);

	if (OtherActor == PlayerCharacter)
	{
		PlayerCharacter->RifeAmmo = PlayerCharacter->RifeAmmo + RifeAmmo;
	}
	else if (OtherActor == EnemyCharacter)
	{
		EnemyCharacter->RifeAmmo = EnemyCharacter->RifeAmmo + RifeAmmo;
	}

}

void ASTKRifleAmmoPickup::SetRifeAmmoNum(AActor* OtherActor)
{
	AShootToKillEnemyRiflemenCharacter* EnemyCharacter = Cast<AShootToKillEnemyRiflemenCharacter>(OtherActor);

	RifeAmmo = RifeAmmo + EnemyCharacter->RifeAmmo;
}