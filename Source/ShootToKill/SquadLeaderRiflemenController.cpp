// Fill out your copyright notice in the Description page of Project Settings.


#include "SquadLeaderRiflemenController.h"
#include "STKEnemySqaudLeaderRiflemen.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ASquadLeaderRiflemenController::ASquadLeaderRiflemenController()
{
	// Sets Behavior tree
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComponent);
	// Sets blackboard
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComponent);
}

void ASquadLeaderRiflemenController::OnPossess(APawn* InPawn)
{
	// Run Behavior tree
	Super::OnPossess(InPawn);
	if (InPawn == nullptr)
	{
		return;
	}
	ASTKEnemySqaudLeaderRiflemen* SquadLeader = Cast<ASTKEnemySqaudLeaderRiflemen>(InPawn);
	if (SquadLeader)
	{
		if (SquadLeader->BehaviorTree)
		{
			BlackboardComponent->InitializeBlackboard(*(SquadLeader->BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*(SquadLeader->BehaviorTree));
		}
	}
}

UBlackboardComponent* ASquadLeaderRiflemenController::GetBlackboard()
{
	return BlackboardComponent;
}