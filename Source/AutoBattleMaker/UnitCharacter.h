// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitCharacter.generated.h"

USTRUCT()
struct FTarget
{
	GENERATED_USTRUCT_BODY()

	/// <summary>
	/// The unit that will act as another's target.
	/// </summary>
	UPROPERTY(EditAnywhere)
	AUnitCharacter* Unit;

	/// <summary>
	/// The amount of priority the target has. If it is the highest in a list, it will become the unit's target.
	/// </summary>
	UPROPERTY(EditAnywhere)
	float Priority;
};

USTRUCT()
struct FUnitStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float SightRange;

	UPROPERTY(EditAnywhere)
	float ActionRange;
};

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

	/// <summary>
	/// Updates all target's priority and updates the target at the end.
	/// </summary>
	virtual void UpdateTarget();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FUnitStats GetUnitStats() { return UnitStats; }

private:
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Radius, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Radius;

	UPROPERTY(EditAnywhere)
	AUnitCharacter* Target;

	UPROPERTY(EditAnywhere)
	FUnitStats UnitStats;

	UPROPERTY(EditAnywhere)
	TArray<FTarget> PotentialTargets;

	class UAIPerceptionComponent* PerceptionComponent;
	class UAISenseConfig_Sight* Sight;
};
