// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MP_PlayerState.h"
#include "Net/UnrealNetwork.h"

AMP_PlayerState::AMP_PlayerState()
{
	// 동기화 빈도를 높게 한다. Pick 을 빨리 먹으면 숫자 올라가는 게 더 빨리 보이도록
	SetNetUpdateFrequency(10.f);
}

void AMP_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AMP_PlayerState, NumPickups);	
}

void AMP_PlayerState::SetNumPickups(int32 Amount)
{
	NumPickups = Amount;
	OnPickupCountChanged.Broadcast(NumPickups);
}

void AMP_PlayerState::OnRep_NumPickups()
{
	OnPickupCountChanged.Broadcast(NumPickups);
}
