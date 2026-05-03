// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MP_PlayerController.h"
#include "UI/MP_PickupCountWidget.h"
#include "MP_PlayerState.h"

void AMP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(!IsLocalController())
		return;

	if (PickupCountWidgetClass)
	{
		PickupCountWidget = CreateWidget<UMP_PickupCountWidget>(this, PickupCountWidgetClass);
		if (PickupCountWidget)
		{
			PickupCountWidget->AddToViewport();
		}
	}

	if(HasAuthority())
	{
		AMP_PlayerState* PS = GetPlayerState<AMP_PlayerState>();
		if(IsValid(PS))
		{
			PS->OnPickupCountChanged.AddDynamic(this, &AMP_PlayerController::OnPickupCountChanged);
		}
	}
}

void AMP_PlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AMP_PlayerState* PS = GetPlayerState<AMP_PlayerState>();
	if(!IsValid(PS))
		return;

	PS->OnPickupCountChanged.AddDynamic(this, &AMP_PlayerController::OnPickupCountChanged);
}

void AMP_PlayerController::OnPickupCountChanged(int32 Count)
{
	if(!IsValid(PickupCountWidget))
		return;

	PickupCountWidget->SetPickupCount(Count);
}
