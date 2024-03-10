// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyRiflemenController.generated.h"

UCLASS()
class SHOOTTOKILL_API AEnemyRiflemenController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyRiflemenController();

	UBlackboardComponent* GetBlackboard();

	virtual void OnPossess(APawn* InPawn) override;

protected:

	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(BlueprintReadWrite, Category = Blackboard)
	class UBlackboardComponent* BlackboardComponent;
};
