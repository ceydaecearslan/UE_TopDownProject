// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClasses/ActorComponent/TopDownAbilitySystemComponent.h"

#include "Data/CharacterClassDataAsset.h"
#include "GameplayAbilitySystem/Abilities/GameplayAbilityBase.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UTopDownAbilitySystemComponent::UTopDownAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTopDownAbilitySystemComponent::InitializeAbilities(TArray<FAbilityData> Abilities)
{
	CooldownMap.Empty();
	for (int i = 0; i < Abilities.Num(); i++)
	{
		FAbilityData Ability = Abilities[i];
		UGameplayAbilityBase* GameplayAbility = Ability.AbilityClass.GetDefaultObject();
		FGameplayAbilitySpec AbilitySpec(GameplayAbility, 1, 0);
		GiveAbility(AbilitySpec);
		CooldownMap.Add(AbilitySpec.Handle, Ability.Cooldown);
		
		switch (Ability.AbilityType)
		{
		case EAbilityType::Primary:
			PrimaryAbilitySpecHandle = AbilitySpec.Handle;
			break;
		case EAbilityType::Secondary:
			SecondaryAbilitySpecHandle = AbilitySpec.Handle;
			break;
		case EAbilityType::Tertiary:
			TertiaryAbilitySpecHandle = AbilitySpec.Handle;
			break;
		case EAbilityType::Ultimate:
			UltimateAbilitySpecHandle = AbilitySpec.Handle;
			break;
		default:
			break;
		}
		UKismetSystemLibrary::PrintString(GetWorld(), Ability.AbilityClass->GetName(), true, false, FLinearColor::Blue, 5.f);
	}
}

FGameplayAbilitySpecHandle UTopDownAbilitySystemComponent::GetAbilitySpecHandle(EAbilityType AbilityType)
{
	FGameplayAbilitySpecHandle SpecHandle;
	switch (AbilityType)
	{
	case EAbilityType::Primary:
		SpecHandle = PrimaryAbilitySpecHandle;
		break;
	case EAbilityType::Secondary:
		SpecHandle = SecondaryAbilitySpecHandle;
		break;
	case EAbilityType::Tertiary:
		SpecHandle = TertiaryAbilitySpecHandle;
		break;
	case EAbilityType::Ultimate:
		SpecHandle = UltimateAbilitySpecHandle;
		break;
	default:
		break;
	}
	return SpecHandle;
}

bool UTopDownAbilitySystemComponent::GetCooldownForSpecHandle(FGameplayAbilitySpecHandle Handle, float& OutCooldown) const
{
	if (const float* CooldownPtr = CooldownMap.Find(Handle))
	{
		OutCooldown = *CooldownPtr;
		return true;
	}
	return false;
}