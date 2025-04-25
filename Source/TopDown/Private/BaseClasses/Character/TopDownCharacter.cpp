// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDown/Public/BaseClasses/Character/TopDownCharacter.h"

#include "BaseClasses/ActorComponent/CharacterClassComponent.h"
#include "BaseClasses/ActorComponent/TopDownAbilitySystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "GameplayAbilitySystem/AttributeSet/PlayerAttributeSet.h"

ATopDownCharacter::ATopDownCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UTopDownAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("AttributeSet"));
	CharacterClassComponent = CreateDefaultSubobject<UCharacterClassComponent>(TEXT("CharacterClassComponent"));

	OnNewCharacterClassSelected.AddDynamic(this, &ATopDownCharacter::InitializeCharacterClass);
	OnAbilityInputReceived.AddDynamic(this, &ATopDownCharacter::AbilityInputReceived);

}

void ATopDownCharacter::InitializeCharacterClass(FClassData NewData)
{
	CharacterClassComponent->InitializeClassData(NewData);
	AbilitySystemComponent->InitializeAbilities(NewData.Abilities);
}

void ATopDownCharacter::AbilityInputReceived(EAbilityType AbilityType)
{
	FGameplayAbilitySpecHandle AbilityHandle = AbilitySystemComponent->GetAbilitySpecHandle(AbilityType);
	if (AbilityHandle.IsValid())
	{
		AbilitySystemComponent->TryActivateAbility(AbilityHandle);
	}
}
