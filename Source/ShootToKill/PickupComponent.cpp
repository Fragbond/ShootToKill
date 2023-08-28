// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"

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
	if (Character != nullptr)
	{
		OnPickup.Broadcast(Character);

		OnComponentBeginOverlap.RemoveAll(this);
	}
}