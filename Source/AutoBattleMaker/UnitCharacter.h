// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitCharacter.generated.h"

UCLASS()
class AUTOBATTLEMAKER_API AUnitCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnitCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// <summary>
	/// Updates the walk speed of the unit given a certain speed.
	/// </summary>
	/// <param name="speed"> The speed that the unit's walk speed will update to. </param>
	virtual void UpdateWalkSpeed(float speed);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

};
