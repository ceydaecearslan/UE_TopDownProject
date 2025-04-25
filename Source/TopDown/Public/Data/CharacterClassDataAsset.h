// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassDataAsset.generated.h"

/**
 * 
 */

class UGameplayAbilityBase;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	None 	  UMETA(DisplayName = "None"),
	Warrior     UMETA(DisplayName = "Warrior"),
	Mage        UMETA(DisplayName = "Mage"),
	Rogue       UMETA(DisplayName = "Rogue"),
	Archer      UMETA(DisplayName = "Archer"),
	Cleric      UMETA(DisplayName = "Cleric")
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	Primary,
	Secondary,
	Tertiary,
	Ultimate
};

USTRUCT(BlueprintType)
struct FAbilityData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UGameplayAbilityBase> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	EAbilityType AbilityType;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	FText CharacterClassDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	UTexture2D* ClassIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Info")
	FText ClassDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<FAbilityData> Abilities;
};

UCLASS()
class TOPDOWN_API UCharacterClassDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION()
	FClassData GetClassData(ECharacterClass Class) const
	{
		for (const FClassData& ClassData : Classes)
		{
			if (ClassData.CharacterClass == Class)
			{
				return ClassData;
			}
		}
		return FClassData();
	}

	UFUNCTION()
	TArray<FAbilityData> GetAbilities(ECharacterClass Class) const
	{
		for (const FClassData& ClassData : Classes)
		{
			if (ClassData.CharacterClass == Class)
			{
				return ClassData.Abilities;
			}
		}
		return TArray<FAbilityData>();
	}

	UFUNCTION()
	TArray<FClassData> GetClasses() const
	{
		return Classes;
	}
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FClassData> Classes;
};
