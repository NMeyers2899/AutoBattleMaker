// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrol.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <NavigationSystem.h>

EBTNodeResult::Type UBTTask_FindPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Gets the unit.
	AAIController* controller = OwnerComp.GetAIOwner();

	// If there is no unit, fail the process.
	if (!controller)
		return EBTNodeResult::Failed;


	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(controller->GetOwner());
	FNavLocation PatrolLocation;

	//// Checks to see if a point can be found in the unit's radius. If it is, set the patrol location on the blackboard to that found value.
	//if (navSystem->GetRandomReachablePointInRadius(controller->GetOwner()->GetActorLocation(), Radius, PatrolLocation))
	//{
	//	controller->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", PatrolLocation.Location);
	//}
	//// If it is not, make the patrol location the unit's current location.
	//else
	//{
	//	controller->GetBlackboardComponent()->SetValueAsVector("PatrolLocation", controller->GetOwner()->GetActorLocation());
	//}

	return EBTNodeResult::Succeeded;
}
