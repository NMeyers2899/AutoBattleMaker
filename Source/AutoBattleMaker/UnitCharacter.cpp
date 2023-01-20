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
	Sight->PeripheralVisionAngleDegrees = 90.0f;

	// Adds the unit's OnPerception function to the Perception Component's OnTargetPerceptionUpdated delegate.
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AUnitCharacter::OnPerception);
}

// Called when the game starts or when spawned
void AUnitCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Create an initial target using this unit.
	FTarget target;
	target.Unit = this;
	target.Priority = 0.0f;
	PotentialTargets.Init(target, 1);
}

void AUnitCharacter::UpdateWalkSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void AUnitCharacter::UpdateTarget()
{
	// Create a new list for targets.
	TArray<FTarget> newTargetList;
	for (int i = 0; i < PotentialTargets.Num(); i++)
	{
		// If that target has a different affiliation or is still in sight range, add it to the new list.
		if (PotentialTargets[i].Unit->Affiliation != Affiliation || Sight->LoseSightRadius > FVector::Dist(GetActorLocation(), PotentialTargets[i].Unit->GetActorLocation()))
		{
			newTargetList.Add(PotentialTargets[i]);
		}
	}

	// Set the Potential Targets list to the new list.
	PotentialTargets = newTargetList;

	// Create a temporary target.
	FTarget currentTarget;
	currentTarget.Priority = 0;

	// Increase priority on each potential target and set the target as the one with the highest priority.
	for (int i = 0; i < PotentialTargets.Num(); i++)
	{
		// If this unit is its own target, increase its priority minimally. Otherwise, increase it normally.
		if(PotentialTargets[i].Unit == this)
			PotentialTargets[i].Priority += 0.001;
		else
			PotentialTargets[i].Priority += 0.01;

		if (PotentialTargets[i].Priority > currentTarget.Priority)
			currentTarget = PotentialTargets[i];
	}

	Target = currentTarget.Unit;
}

// Called every frame
void AUnitCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Sets up the range at which the unit will be able to percieve other units entering their sight range.
	Sight->SightRadius = UnitStats.SightRange;
	Sight->LoseSightRadius = UnitStats.SightRange * 1.25f;


	// If this unit is in acting range of its target, tell it to stop moving.
	if (Target && FVector::Dist(GetActorLocation(), GetTarget()->GetActorLocation()) < GetUnitStats().ActionRange)
		UpdateWalkSpeed(0.0f);
	else
		UpdateWalkSpeed(UnitStats.MovementSpeed);
}

// Called to bind functionality to input
void AUnitCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AUnitCharacter::Act()
{
	// If the units have the same affiliation, don't continue.
	if (Target->Affiliation == Affiliation)
		return;

	// Set the target's affiliation to this one's.
	Target->Affiliation = Affiliation;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, Sight->GetDebugColor(), "Target Assimilated To " + Affiliation);
}

void AUnitCharacter::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	// Creates a new target, and casts the actor that was spotted to a unit character.
	FTarget newTarget;
	newTarget.Unit = dynamic_cast<AUnitCharacter*>(Actor);
	
	// If that actor is not a unit character, return.
	if (!newTarget.Unit || newTarget.Unit->Affiliation == Affiliation)
		return;

	// If there are no elements in the array, simply set the target's priority to zero and add it to the list.
	if (PotentialTargets.Num() == 0)
	{
		newTarget.Priority = 0;
		PotentialTargets.Add(newTarget);
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
}

bool FTarget::operator==(FTarget lhs)
{
	FTarget temp;
	temp.Unit = Unit;

	return temp.Unit == lhs.Unit;
}
