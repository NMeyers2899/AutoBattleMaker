// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrol.h"
#include "UnitCharacter.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <NavigationPath.h>
#include <NavigationSystem.h>

EBTNodeResult::Type UBTTask_FindPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Gets the unit's AI controller.
	AAIController* controller = OwnerComp.GetAIOwner();
	AUnitCharacter* unit = dynamic_cast<AUnitCharacter*>(controller->GetPawn());

	// If there is no unit, fail the process.
	if (!controller)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation PatrolLocation;

	// Checks to see if a point can be found in the unit's radius. If it is, set the patrol location on the blackboard to that found value.
	if (navSystem->GetRandomReachablePointInRadius(controller->GetPawn()->GetActorLocation(), Radius, PatrolLocation))
	{
		controller->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", PatrolLocation.Location);
	}
	// If it is not, make the patrol location the unit's current location.
	else
	{
		controller->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", controller->GetPawn()->GetActorLocation());
	}

	return EBTNodeResult::Succeeded;
}
