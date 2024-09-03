// Fill out your copyright notice in the Description page of Project Settings.


#include "STKSniper.h"

// Sets default values
ASTKSniper::ASTKSniper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTKSniper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTKSniper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTKSniper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASTKSniper::PickupRifeAmmo()
{
	RifeAmmo = RifeAmmo + 10;
}

void ASTKSniper::PickupSmallHealthPack()
{
	Hitpoints = Hitpoints + 20;
}

void ASTKSniper::PickupBigHealthPack()
{
	Hitpoints = Hitpoints + 100;
}