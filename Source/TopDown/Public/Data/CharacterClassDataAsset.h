// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassDataAsset.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Warrior     UMETA(DisplayName = "Warrior"),
	Mage        UMETA(DisplayName = "Mage"),
	Rogue       UMETA(DisplayName = "Rogue"),
	Archer      UMETA(DisplayName = "Archer"),
	Cleric      UMETA(DisplayName = "Cleric")
};

USTRUCT(BlueprintType)
struct FAbilityData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FString AbilityID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FText AbilityDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FText AbilityDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UTexture2D* AbilityIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float Cooldown = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float ManaCost = 0.f;
};

USTRUCT(BlueprintType)
struct FClassData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	ECharacterClass CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<FAbilityData> Abilities;
};

UCLASS()
class TOPDOWN_API UCharacterClassDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<FClassData> Classes;
};
