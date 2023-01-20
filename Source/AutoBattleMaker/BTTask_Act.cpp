// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Act.h"
#include "UnitCharacter.h"
#include <AIController.h>

EBTNodeResult::Type UBTTask_Act::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Check to see if the character is a unit character.
	AUnitCharacter* unit = dynamic_cast<AUnitCharacter*>(OwnerComp.GetAIOwner()->GetPawn());

	// Call the unit to update its targets.
	unit->UpdateTarget();

	// If the unit does not have a target, or the target is this same unit, fail the process.
	if (!unit->GetTarget() || unit->GetTarget() == unit)
		return EBTNodeResult::Failed;

	// If the unit is in acting range, call its act function.
	if (FVector::Dist(unit->GetActorLocation(), unit->GetTarget()->GetActorLocation()) < unit->GetUnitStats().ActionRange)
	{
		unit->Act();
		return EBTNodeResult::Succeeded;
	}
	       
	return EBTNodeResult::Failed;
}
