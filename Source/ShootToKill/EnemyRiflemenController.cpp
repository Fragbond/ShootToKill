// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRiflemenController.h"
#include "ShootToKillEnemyRiflemenCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyRiflemenController::AEnemyRiflemenController()
{
	// Sets Behavior tree
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComponent);
	// Sets blackboard
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComponent);
}

void AEnemyRiflemenController::OnPossess(APawn* InPawn)
{
	// Run Behavior tree
	Super::OnPossess(InPawn);
	if (InPawn == nullptr)
	{
		return;
	}
	AShootToKillEnemyRiflemenCharacter* EnemyRiflemen = Cast<AShootToKillEnemyRiflemenCharacter>(InPawn);
	if (EnemyRiflemen)
	{
		if (EnemyRiflemen->BehaviorTree)
		{
			BlackboardComponent->InitializeBlackboard(*(EnemyRiflemen->BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*(EnemyRiflemen->BehaviorTree));
		}
	}
}

UBlackboardComponent* AEnemyRiflemenController::GetBlackboard()
{
	return BlackboardComponent;
}
