// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/CharacterClassDataAsset.h"
#include "CharacterClassComponent.generated.h"


class ATopDownCharacter;
struct FClassData;
enum class ECharacterClass : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWN_API UCharacterClassComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UCharacterClassComponent();

	UFUNCTION()
	void InitializeClassData(FClassData NewData);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ECharacterClass CharacterClass;

private:

	FClassData ClassData;

};
