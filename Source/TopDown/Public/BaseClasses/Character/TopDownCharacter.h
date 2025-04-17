// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerAttributeSet;
class UAbilitySystemComponent;

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
	
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const
	{
		return AbilitySystemComponent;
	}

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Initialize | GAS")
	TObjectPtr<UPlayerAttributeSet> AttributeSet;
};

