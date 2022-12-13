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

	// Sets up the range at which the unit will be able to percieve other units entering their sight range.
	Sight->SightRadius = UnitStats.SightRange;
	Sight->LoseSightRadius = UnitStats.SightRange + 500;
	Sight->PeripheralVisionAngleDegrees = 90.0f;

	// Sets the perception component's dominant sense to the sight configuration.
	PerceptionComponent->ConfigureSense(*Sight);
	PerceptionComponent->SetDominantSense(Sight->GetSenseImplementation());

	// Adds the unit's OnPerception function to the Perception Component's OnTargetPerceptionUpdated delegate.
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AUnitCharacter::OnPerception);
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

void AUnitCharacter::UpdateTarget()
{
	
}

// Called every frame
void AUnitCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateWalkSpeed(UnitStats.MovementSpeed);
}

// Called to bind functionality to input
void AUnitCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnitCharacter::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
}

