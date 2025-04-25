// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassDataAsset.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

class UTopDownAbilitySystemComponent;
struct FAbilityData;
struct FClassData;
class UCharacterClassComponent;
class USpringArmComponent;
class UCameraComponent;
class UPlayerAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewCharacterClassSelected, FClassData, NewClassData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityInputReceived, EAbilityType, AbilityType);

UCLASS(Blueprintable)
class ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownCharacter();
	
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const
	{
		return TopDownCameraComponent;
	}

	FORCEINLINE USpringArmComponent* GetCameraBoom() const
	{
		return CameraBoom;
	}
	
	FORCEINLINE UTopDownAbilitySystemComponent* GetAbilitySystemComponent() const
	{
		return AbilitySystemComponent;
	}
	
	FORCEINLINE UCharacterClassComponent* GetCharacterClassComponent() const
	{
		return CharacterClassComponent;
	}
	
	FORCEINLINE FOnNewCharacterClassSelected GetOnNewCharacterClassSelected() const
	{
		return OnNewCharacterClassSelected;
	}
	
	FORCEINLINE FOnAbilityInputReceived GetOnAbilityInputReceived() const
	{
		return OnAbilityInputReceived;
	}

protected:

	UFUNCTION()
	void InitializeCharacterClass(FClassData NewData);

	UFUNCTION()
	void AbilityInputReceived(EAbilityType AbilityType);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTopDownAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCharacterClassComponent> CharacterClassComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Initialize | GAS")
	TObjectPtr<UPlayerAttributeSet> AttributeSet;

private:

	FOnNewCharacterClassSelected OnNewCharacterClassSelected;
	FOnAbilityInputReceived OnAbilityInputReceived;
	
};

