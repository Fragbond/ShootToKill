// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"
#include "ShootToKillPlayerCharacter.h"

UPickupComponent::UPickupComponent()
{
	SphereRadius = 32.f;
}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::OnSphereBeginOverlap);
}

void UPickupComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShootToKillPlayerCharacter* Character = Cast<AShootToKillPlayerCharacter>(OtherActor);
	AShootToKillEnemyRiflemenCharacter* AiCharacter = Cast<AShootToKillEnemyRiflemenCharacter>(OtherActor);
	ASTKSquadLeaderCharacter* SquadLeaderCharacter = Cast<ASTKSquadLeaderCharacter>(OtherActor);
	ASTKSniper* SniperCharacter = Cast<ASTKSniper>(OtherActor);
	if (Character != nullptr)
	{
		OnPickup.Broadcast(Character);

		OnComponentBeginOverlap.RemoveAll(this);

	}
	else if (AiCharacter != nullptr)
	{
		OnAiPickup.Broadcast(AiCharacter);

		OnComponentBeginOverlap.RemoveAll(this);
	}
	else if (SquadLeaderCharacter != nullptr)
	{
		OnSquadLeaderPickup.Broadcast(SquadLeaderCharacter);

		OnComponentBeginOverlap.RemoveAll(this);
	}
	else if (SniperCharacter != nullptr)
	{
		OnSniperPickup.Broadcast(SniperCharacter);

		OnComponentBeginOverlap.RemoveAll(this);
	}
}