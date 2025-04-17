// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/WAttributeBar.h"

#include "AbilitySystemComponent.h"
#include "BaseClasses/Character/TopDownCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWAttributeBar::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (ProgressBar)
	{
		ProgressBar->SetFillColorAndOpacity(BarColor);
		FProgressBarStyle ProgressBarStyle = ProgressBar->GetWidgetStyle();
		ProgressBarStyle.BackgroundImage.TintColor = FLinearColor(BarColor.R, BarColor.G, BarColor.B, 0.6f);
		ProgressBar->SetWidgetStyle(ProgressBarStyle);
	}
}

void UWAttributeBar::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!bHasGhostBar)
	{
		ProgressBar_Ghost->RemoveFromParent();
		ProgressBar_Ghost = nullptr;
	}
	
	ATopDownCharacter* PlayerCharacter = Cast<ATopDownCharacter>(GetOwningPlayerPawn());
	if (!PlayerCharacter) return;
	AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if (!AbilitySystemComponent) return;
	if (Attribute.IsValid() && MaxAttribute.IsValid())
	{
		BindToAbilitySystem();
		UpdateProgressBarFirstTime();
		if (ProgressBar_Ghost)
		{
			ProgressBar_Ghost->SetPercent(1);
		}
	}
}
void UWAttributeBar::BindUpdateProgressBar(const FOnAttributeChangeData& Data)
{
    if (!AbilitySystemComponent || !ProgressBar)
        return;

    float CurrentValue = AbilitySystemComponent->GetNumericAttribute(Attribute);
    float MaxValue = AbilitySystemComponent->GetNumericAttribute(MaxAttribute);
    if (MaxValue <= 0.f) return;

    float RealPercent = CurrentValue / MaxValue;
    
    if (Text)
    {
        FString ValueText = FString::Printf(TEXT("%.0f / %.0f"), CurrentValue, MaxValue);
        Text->SetText(FText::FromString(ValueText));
    }

    ProgressBar->SetPercent(RealPercent);
    
	if (ProgressBar_Ghost)
	{
		if (RealPercent < LastRealPercent)
		{
			AnimationStartPercent = LastRealPercent;  
			AnimationTargetPercent = RealPercent;     
			AnimationElapsedTime = 0.0f;              
        
			if (!GetWorld()->GetTimerManager().IsTimerActive(UpdateTimerHandle))
			{
				GetWorld()->GetTimerManager().SetTimer(
					UpdateTimerHandle, 
					this, 
					&UWAttributeBar::UpdateProgressBar, 
					UpdateInterval, 
					true);
			}
		}
		else
		{
			ProgressBar_Ghost->SetPercent(RealPercent);
		}
	}
    LastRealPercent = RealPercent;
}

void UWAttributeBar::UpdateProgressBar()
{
    AnimationElapsedTime += UpdateInterval;
    float Alpha = FMath::Clamp(AnimationElapsedTime / AnimationDuration, 0.0f, 1.0f);
    float NewPercent = FMath::Lerp(AnimationStartPercent, AnimationTargetPercent, Alpha);
    
    ProgressBar_Ghost->SetPercent(NewPercent);
	
    if (Alpha >= 1.0f)
    {
        ProgressBar_Ghost->SetPercent(AnimationTargetPercent);
        GetWorld()->GetTimerManager().ClearTimer(UpdateTimerHandle);
    }
}

void UWAttributeBar::UpdateProgressBarFirstTime()
{
	float NewValue = 0.0f;
	float MaxValue = 0.0f;

	NewValue = AbilitySystemComponent->GetNumericAttribute(Attribute);
	MaxValue = AbilitySystemComponent->GetNumericAttribute(MaxAttribute);
	
	if (ProgressBar && MaxValue > 0.0f)
	{
		ProgressBar->SetPercent(NewValue / MaxValue);
	}
 
	if (Text && AbilitySystemComponent)
	{
		FString HealthText = FString::Printf(TEXT("%.0f / %.0f"), AbilitySystemComponent->GetNumericAttribute(Attribute), AbilitySystemComponent->GetNumericAttribute(MaxAttribute));
		Text->SetText(FText::FromString(HealthText));
	}

}

void UWAttributeBar::BindToAbilitySystem()
{
	if (Attribute.IsValid())
	{
		AttributeChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UWAttributeBar::BindUpdateProgressBar);
	}
	if (MaxAttribute.IsValid())
	{
		AttributeChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UWAttributeBar::BindUpdateProgressBar);
	}
}
