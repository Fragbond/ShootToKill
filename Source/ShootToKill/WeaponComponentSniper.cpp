// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponentSniper.h"
#include "ShootToKillPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "STKSniper.h"

UWeaponComponentSniper::UWeaponComponentSniper()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UWeaponComponentSniper::AttachSniper(AShootToKillPlayerCharacter* TargetCharacter)
{
	PlayerCharacter = TargetCharacter;

	if (PlayerCharacter->HasSniper == false)
	{
		PlayerCharacter->IsRifleEquip = false;
		PlayerCharacter->IsPistolEquip = false;
		PlayerCharacter->IsSniperEquip = true;

		PlayerCharacter->HasSniper = true;

		if (PlayerCharacter == nullptr)
		{
			return;
		}
		// Attachs the gun to the player model
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(PlayerCharacter->GetMesh(), AttachmentRules, FName(TEXT("WeaponGripSocket")));

		// Use to switch character animation. NOTE: This still needs to be added
		PlayerCharacter->SetHasSniper(true);

		if (APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(FireMappingContext, 1);
			}

			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UWeaponComponentSniper::Fire);
			}
		}
	}
	else
	{
		PlayerCharacter->RifeAmmo = PlayerCharacter->RifeAmmo + 30;

		UWeaponComponentSniper::DestroyComponent();
		UWeaponComponentSniper::SetActive(false);

		if (APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(FireMappingContext, 1);
			}

			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UWeaponComponentSniper::Fire);
			}
		}
	}
}

void UWeaponComponentSniper::PutAwaySniper()
{
	UWeaponComponentSniper::SetVisibility(false);
}

void UWeaponComponentSniper::PullOutSniper()
{
	UWeaponComponentSniper::SetVisibility(true);
}

void UWeaponComponentSniper::AttachWeaponToSniper(ASTKSniper* TargetCharacter)
{
	Sniper = TargetCharacter;

	if (Sniper == nullptr)
	{
		return;
	}

	// Attachs the gun to the ai model
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Sniper->GetMesh(), AttachmentRules, FName(TEXT("WeaponGripSocket")));
}

void UWeaponComponentSniper::Fire()
{
	if (PlayerCharacter->IsSniperEquip == true)
	{
		if (PlayerCharacter->RifeAmmo > 0)
		{
			if (PlayerCharacter == nullptr || PlayerCharacter->GetController() == nullptr)
			{
				return;
			}

			if (SniperProjectileClass != nullptr)
			{
				UWorld* const World = GetWorld();
				if (World != nullptr)
				{
					APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
					const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

					const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					World->SpawnActor<ASniperProjectile>(SniperProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				}
			}

			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, PlayerCharacter->GetActorLocation());
			}

			PlayerCharacter->RifeAmmo--;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Your out of ammo."));
		}
	}
}

void UWeaponComponentSniper::SniperFire()
{
	if (Sniper == nullptr || Sniper->GetController() == nullptr)
	{
		return;
	}

	if (Sniper->RifeAmmo > 0)
	{
		if (SniperProjectileClass != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				ASTKSniper* AiPlayer = Cast<ASTKSniper>(Sniper);
				const FRotator SpawnRotation = AiPlayer->K2_GetActorRotation();

				const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				World->SpawnActor<ASniperProjectile>(SniperProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}

		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, Sniper->GetActorLocation());
		}
		Sniper->RifeAmmo--;
	}
	else
	{

	}
}

void UWeaponComponentSniper::EndPlay(const EEndPlayReason::Type EndPlayReason)
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