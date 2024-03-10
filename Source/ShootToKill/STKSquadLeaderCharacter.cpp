// Fill out your copyright notice in the Description page of Project Settings.


#include "STKSquadLeaderCharacter.h"
#include "STKSquadLeaderController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ASTKSquadLeaderCharacter::ASTKSquadLeaderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTKSquadLeaderCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTKSquadLeaderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTKSquadLeaderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASTKSquadLeaderCharacter::PickupRifleAmmo()
{
	RifleAmmo = RifleAmmo + 10;
}

void ASTKSquadLeaderCharacter::PickupSmallHealthPack()
{
	Hitpoints = Hitpoints + 10;
}

void ASTKSquadLeaderCharacter::PickupBigHealthPack()
{
	Hitpoints = Hitpoints + 100;
}