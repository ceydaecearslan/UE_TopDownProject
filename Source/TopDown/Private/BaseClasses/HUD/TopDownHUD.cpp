// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDown/Public/BaseClasses/HUD/TopDownHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/HUD/WTopDownHUD.h"

void ATopDownHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (HUDWidgetClass)
	{
		UWTopDownHUD* HUDWidget = CreateWidget<UWTopDownHUD>(GetWorld(), HUDWidgetClass);
		
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
