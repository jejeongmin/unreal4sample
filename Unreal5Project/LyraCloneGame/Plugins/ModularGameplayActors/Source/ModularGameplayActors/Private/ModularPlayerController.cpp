// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularPlayerController.h"
#include "Components/GameFrameworkComponentManager.h"

void AModularPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void AModularPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);	// 반드시 Super::EndPlay(EndPlayReason) 전에 호출되어야 합니다.

	Super::EndPlay(EndPlayReason);
}
