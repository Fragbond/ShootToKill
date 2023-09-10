// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootToKillEnemyRiflemenCharacter.h"
#include "EnemyRiflemenController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AShootToKillEnemyRiflemenCharacter::AShootToKillEnemyRiflemenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShootToKillEnemyRiflemenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShootToKillEnemyRiflemenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShootToKillEnemyRiflemenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}