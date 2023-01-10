// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Act.h"
#include "UnitCharacter.h"
#include <AIController.h>

EBTNodeResult::Type UBTTask_Act::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AUnitCharacter* unit = dynamic_cast<AUnitCharacter*>(OwnerComp.GetAIOwner()->GetPawn());

	if (!unit->GetTarget() || unit->GetTarget() == unit)
		return EBTNodeResult::Failed;

	if (FVector::Dist(unit->GetActorLocation(), unit->GetTarget()->GetActorLocation()) < unit->GetUnitStats().ActionRange)
	{
		unit->Act();
		return EBTNodeResult::Succeeded;
	}
	       
	return EBTNodeResult::Failed;
}
