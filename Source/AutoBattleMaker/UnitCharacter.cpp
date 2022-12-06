// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitCharacter.h"
#include "LootTableAsset.h"

// Sets default values
AUnitCharacter::AUnitCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnitCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (LootTable)
	{
		for (int i = 0; i < LootTable->Loot.Num(); i++)
		GEngine->AddOnScreenDebugMessage(-1, 3.0, LootTable->Loot[0].Color, LootTable->Loot[0].Name);
	}
	
}

// Called every frame
void AUnitCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUnitCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

