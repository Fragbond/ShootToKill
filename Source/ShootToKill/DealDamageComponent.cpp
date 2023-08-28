// Fill out your copyright notice in the Description page of Project Settings.


#include "DealDamageComponent.h"
#include "Components/CapsuleComponent.h"
#include "ShootToKillPlayerCharacter.h"
#include "GameFramework/DamageType.h"
#include "ShootToKillEnemyCharacter.h"

// Sets default values for this component's properties
UDealDamageComponent::UDealDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapEnd);
}


// Called when the game starts
void UDealDamageComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDealDamageComponent::OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	UE_LOG(LogTemp, Warning, TEXT("UDealDamageComponent::OnOverlapBegin"));

	if (OtherActor == GetOwner())
	{
		return;
	}

	if (!IsActive())
	{
		return;
	}
	
	AShootToKillPlayerCharacter* PlayerCharacter = Cast<AShootToKillPlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetDamage(BaseDamage);
	}

	AShootToKillEnemyCharacter* EnemyCharacter = Cast<AShootToKillEnemyCharacter>(OtherActor);
	if (EnemyCharacter)
	{
		EnemyCharacter->SetDamage(BaseDamage);
	}
}

void UDealDamageComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("UDealDamageComponent::OnOverlapEnd"));
}