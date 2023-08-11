// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "ShootToKillPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

UWeaponComponent::UWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UWeaponComponent::AttachWeapon(AShootToKillPlayerCharacter* TargetCharacter)
{
	PlayerCharacter = TargetCharacter;

	if (PlayerCharacter == nullptr)
	{
		return;
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(PlayerCharacter->GetMesh(), AttachmentRules, FName(TEXT("WeaponGripSocket")));

	PlayerCharacter->SetHasRifle(true);
}