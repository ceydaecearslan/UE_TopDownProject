// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/AttributeSet/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h" 
#include "GameplayAbilitySystem/Effects/HealthRegenerationEffect.h"
#include "GameplayAbilitySystem/Effects/ManaRegenerationEffect.h"
#include "Net/UnrealNetwork.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	Health.SetBaseValue(100);
	Health.SetCurrentValue(100);
	MaxHealth.SetBaseValue(100);
	MaxHealth.SetCurrentValue(100);
	HealthRegenRate.SetBaseValue(1.0f);
	HealthRegenRate.SetCurrentValue(1.0f);
	Mana.SetBaseValue(100);
	Mana.SetCurrentValue(100);
	MaxMana.SetBaseValue(100);
	MaxMana.SetCurrentValue(100);
	ManaRegenRate.SetBaseValue(1.0f);
	ManaRegenRate.SetCurrentValue(1.0f);
	MoveSpeed.SetBaseValue(500.0f);
	MoveSpeed.SetCurrentValue(500.0f);

}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
		if (!ASC) return;
		
		float NewHealth = Health.GetCurrentValue();
		float MaxHealthValue = MaxHealth.GetCurrentValue();

		FGameplayTag HealthRegenTag = FGameplayTag::RequestGameplayTag(FName("Player.Status.RegeneratingHealth"));
		TSubclassOf<UGameplayEffect> HealthRegenEffect = UHealthRegenerationEffect::StaticClass();
		
		if (NewHealth < MaxHealthValue)
		{
			if (!ASC->HasMatchingGameplayTag(HealthRegenTag))
			{
				ASC->GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle, [ASC, HealthRegenTag, HealthRegenEffect]()
				{
					ASC->AddLooseGameplayTag(HealthRegenTag);
					FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
					ASC->ApplyGameplayEffectToSelf(HealthRegenEffect.GetDefaultObject(), 1.0f, EffectContext);
				}, 1.0f, false);
			}
		}
		else
		{
			if (ASC->HasMatchingGameplayTag(HealthRegenTag))
			{
				ASC->RemoveLooseGameplayTag(HealthRegenTag);
				ASC->RemoveActiveGameplayEffectBySourceEffect(HealthRegenEffect, ASC);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
		if (!ASC) return;
		
		float NewMana = Mana.GetCurrentValue();
		float MaxMaxValue = MaxMana.GetCurrentValue();

		FGameplayTag ManaRegenTag = FGameplayTag::RequestGameplayTag(FName("Player.Status.RegeneratingMana"));
		TSubclassOf<UGameplayEffect> ManaRegenEffect = UManaRegenerationEffect::StaticClass();
		
		if (NewMana < MaxMaxValue)
		{
			if (!ASC->HasMatchingGameplayTag(ManaRegenTag))
			{
				ASC->GetWorld()->GetTimerManager().SetTimer(ManaRegenTimerHandle, [ASC, ManaRegenTag, ManaRegenEffect]()
				{
					ASC->AddLooseGameplayTag(ManaRegenTag);
					FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
					ASC->ApplyGameplayEffectToSelf(ManaRegenEffect.GetDefaultObject(), 1.0f, EffectContext);
				}, 1.0f, false);
			}
		}
		else
		{
			if (ASC->HasMatchingGameplayTag(ManaRegenTag))
			{
				ASC->RemoveLooseGameplayTag(ManaRegenTag);
				ASC->RemoveActiveGameplayEffectBySourceEffect(ManaRegenEffect, ASC);
			}
		}
	}
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, HealthRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, ManaRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UPlayerAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Health, OldHealth);
}

void UPlayerAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxHealth, OldMaxHealth);
}

void UPlayerAttributeSet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, HealthRegenRate, OldHealthRegenRate);
}

void UPlayerAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Mana, OldMana);
}

void UPlayerAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxMana, OldMaxMana);
}

void UPlayerAttributeSet::OnRep_ManaRegenRate(const FGameplayAttributeData& OldManaRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, ManaRegenRate, OldManaRegenRate);
}

void UPlayerAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MoveSpeed, OldMoveSpeed);
}