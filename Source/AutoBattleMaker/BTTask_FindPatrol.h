// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrol.generated.h"

/**
 * 
 */
UCLASS()
class AUTOBATTLEMAKER_API UBTTask_FindPatrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	void OnGameplayTaskActivated(UGameplayTask& Task) override {}

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	/// <summary>
	/// How fast the unit will move.
	/// </summary>
	UPROPERTY(EditAnywhere)
	float Speed = 300.0f;

	/// <summary>
	/// The radius in which the unit will seek out its next location.
	/// </summary>
	UPROPERTY(EditAnywhere)
	float Radius = 1000.0f;
	
};
