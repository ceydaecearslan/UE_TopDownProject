// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "WAttributeBar.generated.h"

class UTopDownAbilitySystemComponent;
class UTextBlock;
struct FOnAttributeChangeData;
class UPlayerAttributeSet;
class UProgressBar;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class TOPDOWN_API UWAttributeBar : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	void BindUpdateProgressBar(const FOnAttributeChangeData& Data);
	void UpdateProgressBar();
	void UpdateProgressBarFirstTime();
	void BindToAbilitySystem();
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar_Ghost;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialize | Attribute")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialize | Attribute")
	FGameplayAttribute MaxAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialize | Widget")
	FLinearColor BarColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialize | Widget")
	bool bHasGhostBar = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialize | Widget", meta = (EditCondition = "bHasGhostBar", EditConditionHides))
	FLinearColor GhostBarColor = FLinearColor::Red;

	FDelegateHandle AttributeChangeDelegateHandle;
	FDelegateHandle MaxAttributeChangeDelegateHandle;

	UPROPERTY()
	UTopDownAbilitySystemComponent* AbilitySystemComponent;

private:

	FTimerHandle UpdateTimerHandle;
	float AnimationStartPercent = 1.0f;     
	float AnimationTargetPercent = 1.0f;    
	float AnimationElapsedTime = 0.0f;      
	float AnimationDuration = 0.2f;   
	float LastRealPercent = 1.0f;           
	float UpdateInterval = 0.05f;
	
};
