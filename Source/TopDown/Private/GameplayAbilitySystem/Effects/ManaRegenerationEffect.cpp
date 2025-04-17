// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Effects/ManaRegenerationEffect.h"

#include "GameplayAbilitySystem/AttributeSet/PlayerAttributeSet.h"

UManaRegenerationEffect::UManaRegenerationEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	Period = 1.0f;
	
	FGameplayModifierInfo ManaRegenModifier;
	ManaRegenModifier.Attribute = UPlayerAttributeSet::GetManaAttribute();
	ManaRegenModifier.ModifierOp = EGameplayModOp::Additive;
	ManaRegenModifier.ModifierMagnitude = FScalableFloat(1.f); 
	
	Modifiers.Add(ManaRegenModifier);
}
