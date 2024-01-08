// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootToKillPlayerCharacter.h"
#include "ShootToKillEnemyRiflemenCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WeaponComponentRife.h"
#include "WeaponComponentPistol.h"
#include "PickupComponent.h"

// Sets default values
AShootToKillPlayerCharacter::AShootToKillPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCameraComponent->SetupAttachment(GetMesh());
	PlayerCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AShootToKillPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void AShootToKillPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShootToKillPlayerCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShootToKillPlayerCharacter::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(EquipRifleAction, ETriggerEvent::Triggered, this, &AShootToKillPlayerCharacter::EquipRifle);
		EnhancedInputComponent->BindAction(EquipPistolAction, ETriggerEvent::Triggered, this, &AShootToKillPlayerCharacter::EquipPistol);
	}
}

void AShootToKillPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Adds movement
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AShootToKillPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Adds yaw and pitch input
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AShootToKillPlayerCharacter::EquipRifle(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if (bHasRifle == true)
		{
			IsRifleEquip = true;
			IsPistolEquip = false;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Don't have rifle."));
		}
	}
}

void AShootToKillPlayerCharacter::EquipPistol(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if (bHasPistol == true)
		{
			IsRifleEquip = false;
			IsPistolEquip = true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Don't have pistol."));
		}
	}
}

void AShootToKillPlayerCharacter::IsAlive()
{
	if (Hitpoints <= 0)
	{
		// Need to add death timer function and death timer finish function.
		GetWorld()->GetTimerManager().SetTimer(RestartLevelTimerHandle, this, &AShootToKillPlayerCharacter::OnDeathTimerFinished, TimeRestartLevelAfterDeath, false);
	}
}

void AShootToKillPlayerCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AShootToKillPlayerCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AShootToKillPlayerCharacter::SetHasPistol(bool bNewHasPistol)
{
	bHasPistol = bNewHasPistol;
}

bool AShootToKillPlayerCharacter::GetHasPistol()
{
	return bHasPistol;
}

void AShootToKillPlayerCharacter::OnDeath(bool IsFellOut)
{
	// Need to add death timer function and death timer finish function.
	GetWorld()->GetTimerManager().SetTimer(RestartLevelTimerHandle, this, &AShootToKillPlayerCharacter::OnDeathTimerFinished, TimeRestartLevelAfterDeath, false);
}

void AShootToKillPlayerCharacter::OnDeathTimerFinished()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}

void AShootToKillPlayerCharacter::PickupRifeAmmo()
{
	RifeAmmo = RifeAmmo + 10;
}

void AShootToKillPlayerCharacter::PickupPistolAmmo()
{
	PistolAmmo = PistolAmmo + 10;
}

void AShootToKillPlayerCharacter::PickupSmallHealthPack()
{
	Hitpoints = Hitpoints + 20;
}

void AShootToKillPlayerCharacter::PickupBigHealthPack()
{
	Hitpoints = Hitpoints + 100;
}