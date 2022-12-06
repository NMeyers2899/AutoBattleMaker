// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTableAsset.generated.h"

USTRUCT()
struct FItemInfo {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere)
	FColor Color;

	UPROPERTY(EditAnywhere)
	UBlueprint* Blueprint;
};

/**
 * Loot Table
 */
UCLASS()
class AUTOBATTLEMAKER_API ULootTableAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FItemInfo> Loot;
};
