// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChaseTarget.h"
#include "UnitCharacter.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

EBTNodeResult::Type UBTTask_ChaseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Check to see if the character is a unit character.
	AUnitCharacter* unit = dynamic_cast<AUnitCharacter*>(OwnerComp.GetAIOwner()->GetPawn());

	// If the unit does not have a target, or the target is this same unit, fail the process.
	if (!unit->GetTarget() || unit->GetTarget() == unit)
		return EBTNodeResult::Failed;

	// As long as the unit is not the target, or it is not in acting range of its target, set its target location to its target's position.
	if (unit->GetTarget() != unit && FVector::Dist(unit->GetActorLocation(), unit->GetTarget()->GetActorLocation()) >= unit->GetUnitStats().ActionRange)
	{
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector("TargetLocation", unit->GetTarget()->GetActorLocation());

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}