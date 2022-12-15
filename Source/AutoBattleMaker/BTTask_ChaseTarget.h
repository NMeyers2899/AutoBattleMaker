// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChaseTarget.generated.h"

/**
 * 
 */
UCLASS()
class AUTOBATTLEMAKER_API UBTTask_ChaseTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	void OnGameplayTaskActivated(UGameplayTask& Task) override {}

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
