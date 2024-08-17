// Fill out your copyright notice in the Description page of Project Settings.


#include "SniperController.h"
#include "STKSniper.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ASniperController::ASniperController()
{
	//Sets Behavior tree.
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComponent);
	// Sets blackboard.
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(BlackboardComponent);
}

void ASniperController::OnPossess(APawn* InPawn)
{
	// Runs the behavior tree.
	Super::OnPossess(InPawn);
	if (InPawn == nullptr)
	{
		return;
	}
	ASTKSniper* SniperCharacter = Cast<ASTKSniper>(InPawn);
	if (SniperCharacter)
	{
		if (SniperCharacter->BehaviorTree)
		{
			BlackboardComponent->InitializeBlackboard(*(SniperCharacter->BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*(SniperCharacter->BehaviorTree));
		}
	}
}

UBlackboardComponent* ASniperController::GetBlackboard()
{
	return BlackboardComponent;
}