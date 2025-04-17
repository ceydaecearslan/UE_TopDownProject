// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Effects/HealthRegenerationEffect.h"

#include "GameplayAbilitySystem/AttributeSet/PlayerAttributeSet.h"

UHealthRegenerationEffect::UHealthRegenerationEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 1.0f;
	
	FGameplayModifierInfo HealthRegenModifier;
	HealthRegenModifier.Attribute = UPlayerAttributeSet::GetHealthAttribute();
	HealthRegenModifier.ModifierOp = EGameplayModOp::Additive;
	HealthRegenModifier.ModifierMagnitude = FScalableFloat(1.f); 
	
	Modifiers.Add(HealthRegenModifier);
}
