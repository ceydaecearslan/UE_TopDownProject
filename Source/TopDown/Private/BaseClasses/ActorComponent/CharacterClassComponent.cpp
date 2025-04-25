// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClasses/ActorComponent/CharacterClassComponent.h"

#include "Kismet/KismetSystemLibrary.h"

UCharacterClassComponent::UCharacterClassComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ClassData.CharacterClass = ECharacterClass::None;
}

void UCharacterClassComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterClassComponent::InitializeClassData(FClassData NewData)
{
	ClassData = NewData;
	CharacterClass = ClassData.CharacterClass;
	
	UKismetSystemLibrary::PrintString(GetWorld(), ClassData.CharacterClassDisplayName.ToString(), true, false, FLinearColor::Red, 5.f);
}
