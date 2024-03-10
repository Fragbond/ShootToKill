// Fill out your copyright notice in the Description page of Project Settings.


#include "STKSquadLeaderController.h"
#include "STKSquadLeaderCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTKSquadLeaderController::ASTKSquadLeaderController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComponent);

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComponent);
}


void ASTKSquadLeaderController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn == nullptr)
	{
		return;
	}
	ASTKSquadLeaderCharacter* SquadLeaderCharacter = Cast<ASTKSquadLeaderCharacter>(InPawn);
	if (SquadLeaderCharacter)
	{
		if (SquadLeaderCharacter->BehaviorTree)
		{
			BlackboardComponent->InitializeBlackboard(*(SquadLeaderCharacter->BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*(SquadLeaderCharacter->BehaviorTree));
		}
	}
}

UBlackboardComponent* ASTKSquadLeaderController::GetBlackboard()
{
	return BlackboardComponent;
}