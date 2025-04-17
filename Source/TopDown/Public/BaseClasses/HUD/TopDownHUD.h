// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TopDownHUD.generated.h"

class UWTopDownHUD;
/**
 * 
 */
UCLASS()
class TOPDOWN_API ATopDownHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Initialize")
	TSubclassOf<UWTopDownHUD> HUDWidgetClass;
};
