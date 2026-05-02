// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MP_PlayerState.h"
#include "Net/UnrealNetwork.h"

void AMP_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AMP_PlayerState, NumPickups);	
}
