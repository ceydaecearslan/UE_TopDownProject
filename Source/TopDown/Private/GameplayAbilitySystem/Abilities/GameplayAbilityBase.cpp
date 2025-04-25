// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Abilities/GameplayAbilityBase.h"

#include "BaseClasses/ActorComponent/TopDownAbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UGameplayAbilityBase::UGameplayAbilityBase()
{
	
}

void UGameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FText AbilityActivatedText = FText::Format(FText::FromString("{0} Activated"), GetClass()->GetDisplayNameText());
	UKismetSystemLibrary::PrintString(GetWorld(), AbilityActivatedText.ToString(), true, false, FLinearColor::Black, 5.f);

	ApplyCooldown(Handle, ActorInfo, ActivationInfo);
}

void UGameplayAbilityBase::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect();
	if (CooldownEffect)
	{
		float Cooldown = 0.f;

		if (const UTopDownAbilitySystemComponent* ASC = Cast<UTopDownAbilitySystemComponent>(ActorInfo->AbilitySystemComponent))
		{
			ASC->GetCooldownForSpecHandle(Handle, Cooldown);
		}

		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownEffect->GetClass(), GetAbilityLevel());
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Player.Ability.CooldownDuration")), Cooldown);
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}
