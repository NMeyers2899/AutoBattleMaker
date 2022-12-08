// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitAIController.h"
#include "UnitCharacter.h"
#include <BehaviorTree/BehaviorTree.h>

void AUnitAIController::OnPossess(APawn* InPawn)
{
	AController::OnPossess(InPawn);

	if (!RunBehaviorTree(BehaviorTree))
		return;
}