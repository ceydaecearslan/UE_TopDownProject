// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Data/CharacterClassDataAsset.h"
#include "GameplayAbilitySystem/Abilities/GameplayAbilityBase.h"
#include "TopDownAbilitySystemComponent.generated.h"


enum class EAbilityType : uint8;
class UGameplayAbilityBase;
struct FAbilityData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWN_API UTopDownAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTopDownAbilitySystemComponent();

	void InitializeAbilities(TArray<FAbilityData> Abilities);

	FGameplayAbilitySpecHandle GetAbilitySpecHandle(EAbilityType AbilityType);
	bool GetCooldownForSpecHandle(FGameplayAbilitySpecHandle Handle, float& OutCooldown) const;
	
protected:

	UPROPERTY()
	FGameplayAbilitySpecHandle PrimaryAbilitySpecHandle;

	UPROPERTY()
	FGameplayAbilitySpecHandle SecondaryAbilitySpecHandle;

	UPROPERTY()
	FGameplayAbilitySpecHandle TertiaryAbilitySpecHandle;

	UPROPERTY()
	FGameplayAbilitySpecHandle UltimateAbilitySpecHandle;

	UPROPERTY()
	TMap<FGameplayAbilitySpecHandle, float> CooldownMap;

};
