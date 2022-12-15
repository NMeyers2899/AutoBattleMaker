// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/SphereComponent.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>

// Sets default values
AUnitCharacter::AUnitCharacter()
{
 	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create objects for the perception component and sight configuration.
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	// Sets the perception component's dominant sense to the sight configuration.
	PerceptionComponent->ConfigureSense(*Sight);
	PerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());

	// Adds the unit's OnPerception function to the Perception Component's OnTargetPerceptionUpdated delegate.
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AUnitCharacter::OnPerception);

	FTarget target;
	PotentialTargets.Init(target, 0);
}

// Called when the game starts or when spawned
void AUnitCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AUnitCharacter::UpdateWalkSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

AUnitCharacter* AUnitCharacter::UpdateTarget()
{
	// Create a new array of potential targets and check to see the distance between each target and this unit.
	TArray<FTarget> newTargetList;
	for (int i = 0; i < PotentialTargets.Num(); i++)
	{
		// If that target is close enough, add it to the new list.
		if (Sight->LoseSightRadius > FVector::Dist(GetActorLocation(), PotentialTargets[i].Unit->GetActorLocation()))
			newTargetList.Add(PotentialTargets[i]);
		else if (Target == PotentialTargets[i].Unit)
			Target = NULL;
	}

	PotentialTargets = newTargetList;

	FTarget currentTarget;
	currentTarget.Priority = 0;

	for (int i = 0; i < PotentialTargets.Num(); i++)
	{
		PotentialTargets[i].Priority += 0.001;

		if (PotentialTargets[i].Priority > currentTarget.Priority)
			currentTarget = PotentialTargets[i];
	}

	return currentTarget.Unit;
}

// Called every frame
void AUnitCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateWalkSpeed(UnitStats.MovementSpeed);

	// Sets up the range at which the unit will be able to percieve other units entering their sight range.
	Sight->SightRadius = UnitStats.SightRange;
	Sight->LoseSightRadius = UnitStats.SightRange + 500;
	Sight->PeripheralVisionAngleDegrees = 70.0f;

	Target = UpdateTarget();
}

// Called to bind functionality to input
void AUnitCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AUnitCharacter::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	// Creates a new target, and casts the actor that was spotted to a unit character.
	FTarget newTarget;
	newTarget.Unit = dynamic_cast<AUnitCharacter*>(Actor);
	
	// If that actor is not a unit character, return.
	if (!newTarget.Unit)
		return;

	// If there are no elements in the array, simply set the target's priority to zero and add it to the list.
	if (PotentialTargets.Num() == 0)
	{
		newTarget.Priority = 0;
		PotentialTargets.Add(newTarget);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, Sight->GetDebugColor(), "Target Added");
		return;
	}

	// Checks through the list of potential targets to see if the unit is already in the list as a target. If it is, return.
	for (int i = 0; i < PotentialTargets.Num(); i++)
	{
		if (newTarget.Unit == PotentialTargets[i].Unit)
			return;
	}

	// Set the priority on the target to zero, and then add it to the list.
	newTarget.Priority = 0;
	PotentialTargets.Add(newTarget);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, Sight->GetDebugColor(), "Target Added");
}

