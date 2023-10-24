// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponentPistol.h"
#include "ShootToKillPlayerCharacter.h"
#include "ShootToKillProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UWeaponComponentPistol::UWeaponComponentPistol()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UWeaponComponentPistol::AttachPistol(AShootToKillPlayerCharacter* TargetCharacter)
{
	PlayerCharacter = TargetCharacter;

	PlayerCharacter->IsRifleEquip = false;
	PlayerCharacter->IsPistolEquip = true;

	if (PlayerCharacter == nullptr)
	{
		return;
	}
	// Attachs the gun to the player model
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(PlayerCharacter->GetMesh(), AttachmentRules, FName(TEXT("WeaponGripSocket")));

	// Use to switch character animation. NOTE: This still needs to be added
	PlayerCharacter->SetHasPistol(true);

	if (APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UWeaponComponentPistol::Fire);
		}
	}
}

void UWeaponComponentPistol::PutAwayPistol()
{
	UWeaponComponentPistol::SetVisibility(false);
}

void UWeaponComponentPistol::PullOutPistol()
{
	UWeaponComponentPistol::SetVisibility(true);
}

void UWeaponComponentPistol::Fire()
{
	if (PlayerCharacter->IsPistolEquip == true)
	{
		if (PlayerCharacter->PistolAmmo > 0)
		{
			if (PlayerCharacter == nullptr || PlayerCharacter->GetController() == nullptr)
			{
				return;
			}

			if (ProjectileClass != nullptr)
			{
				UWorld* const World = GetWorld();
				if (World != nullptr)
				{
					APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
					const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

					const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					World->SpawnActor<AShootToKillProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				}
			}

			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, PlayerCharacter->GetActorLocation());
			}

			PlayerCharacter->PistolAmmo--;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Your out of ammo."));
		}
	}
}

void UWeaponComponentPistol::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}