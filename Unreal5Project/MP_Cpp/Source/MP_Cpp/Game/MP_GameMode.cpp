// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MP_GameMode.h"
#include "Game/MP_GameState.h"

AMP_GameMode::AMP_GameMode()
{
	bDelayedStart = true;
	MatchStartDelay = 5.f;
	bUseSeamlessTravel = true;
}

void AMP_GameMode::StartMatch()
{
	Super::StartMatch();

	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Orange, TEXT("Match Started"));
}

void AMP_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);


	AMP_GameState* MPGameState = GetGameState<AMP_GameState>();
	if (IsValid(MPGameState))
	{
		MPGameState->AddTeamMember(NewPlayer);
	}
}

void AMP_GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (bDelayedStart)
	{
		GetWorldTimerManager().SetTimer(MatchStartTimer, this, &ThisClass::StartDelayFinished, MatchStartDelay, false);
	}
}

void AMP_GameMode::StartDelayFinished()
{
	StartMatch();
}
