// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootToKillEnemyCharacter.h"
#include "HealthComponent.h"
#include "DamageComponent.h"

// Sets default values
AShootToKillEnemyCharacter::AShootToKillEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComponent"));
}

// Called when the game starts or when spawned
void AShootToKillEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShootToKillEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShootToKillEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AShootToKillEnemyCharacter::SetDamage(float BaseDamage)
{
	if (DamageComponent)
	{
		DamageComponent->TakeDamage(BaseDamage);
	}
}

void AShootToKillEnemyCharacter::OnDeath(bool IsFellOut)
{
	Destroy();
}

float AShootToKillEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("AShootToKillPlayerCharacter::TakeDamage %.2f"), Damage);
	if (HealthComponent && !HealthComponent->IsDead())
	{
		HealthComponent->TakeDamage(Damage);
		if (HealthComponent->IsDead())
		{
			OnDeath(false);
		}
	}
	return Damage;
}

const bool AShootToKillEnemyCharacter::IsAlive() const
{
	if (HealthComponent)
	{
		return !HealthComponent->IsDead();
	}
	return false;
}

const float AShootToKillEnemyCharacter::GetPlayersCurrentHealth() const
{
	if (HealthComponent)
	{
		return HealthComponent->GetPlayerCurrentHealth();
	}
	return 0.0f;
}