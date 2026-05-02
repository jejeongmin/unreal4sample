// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MP_GameState.h"
#include "Net/UnrealNetwork.h"

void AMP_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMP_GameState, TeamOne);
	DOREPLIFETIME(AMP_GameState, TeamTwo);
}

void AMP_GameState::AddTeamMember(APlayerController* PlayerController)
{
	if (TeamOne.Num() > TeamTwo.Num())
	{
		TeamTwo.Add(PlayerController);
	}
	else
	{
		TeamOne.Add(PlayerController);
	}
}

bool AMP_GameState::IsTeamOne(APlayerController* PlayerController) const
{
	return TeamOne.Contains(PlayerController);
}

bool AMP_GameState::IsTeamTwo(APlayerController* PlayerController) const
{
	return TeamTwo.Contains(PlayerController);
}