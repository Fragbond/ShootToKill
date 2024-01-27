// Fill out your copyright notice in the Description page of Project Settings.


#include "STKEnemySqaudLeaderRiflemen.h"
#include "SquadLeaderRiflemenController.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
ASTKEnemySqaudLeaderRiflemen::ASTKEnemySqaudLeaderRiflemen()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTKEnemySqaudLeaderRiflemen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTKEnemySqaudLeaderRiflemen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto FollowPoint : FollowPoints)
	{
		WorldFollowPoints.Add(FollowPoint + GetActorLocation());
	}
}

// Called to bind functionality to input
void ASTKEnemySqaudLeaderRiflemen::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASTKEnemySqaudLeaderRiflemen::PickupRifeAmmo()
{
	RifeAmmo = RifeAmmo + 10;
}

void ASTKEnemySqaudLeaderRiflemen::PickupSmallHealthPack()
{
	Hitpoints = Hitpoints + 20;
}

void ASTKEnemySqaudLeaderRiflemen::PickupBigHealthPack()
{
	Hitpoints = Hitpoints + 100;
}