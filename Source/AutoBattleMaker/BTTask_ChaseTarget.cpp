// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChaseTarget.h"
#include "UnitCharacter.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

EBTNodeResult::Type UBTTask_ChaseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AUnitCharacter* unit = dynamic_cast<AUnitCharacter*>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if (!unit->GetTarget() || FVector::Dist(unit->GetActorLocation(), unit->GetTarget()->GetActorLocation()) < unit->GetUnitStats().ActionRange)
			return EBTNodeResult::Failed;

		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector("TargetLocation", unit->GetTarget()->GetActorLocation());

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}