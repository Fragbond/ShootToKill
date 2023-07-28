// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupWeaponComponent.h"

UPickupWeaponComponent::UPickupWeaponComponent()
{
	SphereRadius = 32.f;
}

void UPickupWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UPickupWeaponComponent::OnSphereBeginOverlap);
}

void UPickupWeaponComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShootToKillPlayerCharacter* Character = Cast<AShootToKillPlayerCharacter>(OtherActor);
	if (Character != nullptr)
	{
		OnPickup.Broadcast(Character);

		OnComponentBeginOverlap.RemoveAll(this);
	}
}