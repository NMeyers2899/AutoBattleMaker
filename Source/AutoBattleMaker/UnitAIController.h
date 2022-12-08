// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

/**
 * 
 */
UCLASS()
class AUTOBATTLEMAKER_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

public:
	void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;
	
};
