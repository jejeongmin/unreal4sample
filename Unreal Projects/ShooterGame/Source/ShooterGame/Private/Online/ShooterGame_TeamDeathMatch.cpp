// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "ShooterTeamStart.h"
#include "Online/ShooterGame_TeamDeathMatch.h"
#include "Online/ShooterPlayerState.h"
#include "Bots/ShooterAIController.h"

AShooterGame_TeamDeathMatch::AShooterGame_TeamDeathMatch(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NumTeams = 2;
	bDelayedStart = true;
}

void AShooterGame_TeamDeathMatch::PostLogin(APlayerController* NewPlayer)
{
	// Place player on a team before Super (VoIP team based init, findplayerstart, etc)
	AShooterPlayerState* NewPlayerState = CastChecked<AShooterPlayerState>(NewPlayer->PlayerState);
	const int32 TeamNum = ChooseTeam(NewPlayerState);
	NewPlayerState->SetTeamNum(TeamNum);

	Super::PostLogin(NewPlayer);
}

void AShooterGame_TeamDeathMatch::InitGameState()
{
	Super::InitGameState();

	AShooterGameState* const MyGameState = Cast<AShooterGameState>(GameState);
	if (MyGameState)
	{
		MyGameState->NumTeams = NumTeams;
	}
}

/*
	jejeongmin	2019-05-19

	TDM 이기 때문에 같은 팀이 주는 대미지는 안받지만, 스스로에게 가한 데미지(폭딜/스플래시 대미지)는 받는다.
*/
bool AShooterGame_TeamDeathMatch::CanDealDamage(AShooterPlayerState* DamageInstigator, class AShooterPlayerState* DamagedPlayer) const
{
	return DamageInstigator && DamagedPlayer && (DamagedPlayer == DamageInstigator || DamagedPlayer->GetTeamNum() != DamageInstigator->GetTeamNum());
}

int32 AShooterGame_TeamDeathMatch::ChooseTeam(AShooterPlayerState* ForPlayerState) const
{
	TArray<int32> TeamBalance;
	TeamBalance.AddZeroed(NumTeams);

	// get current team balance
	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		AShooterPlayerState const* const TestPlayerState = Cast<AShooterPlayerState>(GameState->PlayerArray[i]);
		if (TestPlayerState && TestPlayerState != ForPlayerState && TeamBalance.IsValidIndex(TestPlayerState->GetTeamNum()))
		{
			TeamBalance[TestPlayerState->GetTeamNum()]++;
		}
	}

	// find least populated one
	int32 BestTeamScore = TeamBalance[0];
	for (int32 i = 1; i < TeamBalance.Num(); i++)
	{
		if (BestTeamScore > TeamBalance[i])
		{
			BestTeamScore = TeamBalance[i];
		}
	}

	// there could be more than one...
	TArray<int32> BestTeams;
	for (int32 i = 0; i < TeamBalance.Num(); i++)
	{
		if (TeamBalance[i] == BestTeamScore)
		{
			BestTeams.Add(i);
		}
	}

	// get random from best list
	const int32 RandomBestTeam = BestTeams[FMath::RandHelper(BestTeams.Num())];
	return RandomBestTeam;
}

void AShooterGame_TeamDeathMatch::DetermineMatchWinner()
{
	AShooterGameState const* const MyGameState = Cast<AShooterGameState>(GameState);
	int32 BestScore = MIN_uint32;
	int32 BestTeam = -1;
	int32 NumBestTeams = 1;

	for (int32 i = 0; i < MyGameState->TeamScores.Num(); i++)
	{
		const int32 TeamScore = MyGameState->TeamScores[i];
		if (BestScore < TeamScore)
		{
			BestScore = TeamScore;
			BestTeam = i;
			NumBestTeams = 1;
		}
		else if (BestScore == TeamScore)
		{
			NumBestTeams++;
		}
	}

	WinnerTeam = (NumBestTeams == 1) ? BestTeam : NumTeams;
}

bool AShooterGame_TeamDeathMatch::IsWinner(AShooterPlayerState* PlayerState) const
{
	return PlayerState && !PlayerState->IsQuitter() && PlayerState->GetTeamNum() == WinnerTeam;
}

/*
	jejeongmin	2019-05-19
	
	SpawnPoint 에 team 정보가 있으므로, 해당 point 에서는 같은 팀의 pawn 만 스폰할 수 있다.
*/
bool AShooterGame_TeamDeathMatch::IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const
{
	if (Player)
	{
		AShooterTeamStart* TeamStart = Cast<AShooterTeamStart>(SpawnPoint);
		AShooterPlayerState* PlayerState = Cast<AShooterPlayerState>(Player->PlayerState);

		if (PlayerState && TeamStart && TeamStart->SpawnTeam != PlayerState->GetTeamNum())
		{
			return false;
		}
	}

	return Super::IsSpawnpointAllowed(SpawnPoint, Player);
}

/*
	jejeongmin	2019-05-19

	AI pawn 도 초기화할 때 어느 팀인지 정해준다.
*/
void AShooterGame_TeamDeathMatch::InitBot(AShooterAIController* AIC, int32 BotNum)
{	
	AShooterPlayerState* BotPlayerState = CastChecked<AShooterPlayerState>(AIC->PlayerState);
	const int32 TeamNum = ChooseTeam(BotPlayerState);
	BotPlayerState->SetTeamNum(TeamNum);		

	Super::InitBot(AIC, BotNum);
}