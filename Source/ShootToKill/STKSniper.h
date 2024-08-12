// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STKSniper.generated.h"

UCLASS()
class SHOOTTOKILL_API ASTKSniper : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTKSniper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Hitpoints = 75;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsDead = false;
};
