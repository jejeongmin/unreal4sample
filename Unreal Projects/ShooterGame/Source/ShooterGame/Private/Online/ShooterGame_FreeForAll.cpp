// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "ShooterGame_FreeForAll.h"
#include "ShooterPlayerState.h"

AShooterGame_FreeForAll::AShooterGame_FreeForAll(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bDelayedStart = true;
}

/*
	jejeongmin	2019-05-19

	유저 중 최고 점수 획득한 사람을 winer 로 결정한다.
	TDM 이 winer team 을 선정하는 것에 비해 이것은 한 유저의 WinnerPlayerState 를 선정한다.
	아마 이게 이 함수의 반환값이 void 인 이유인가보다.
	동점자가 존재하는 경우에는 다른 요인을 고려하지 않고 승자를 정하지 않게 기본 구현되어 있다.
*/
void AShooterGame_FreeForAll::DetermineMatchWinner()
{
	AShooterGameState const* const MyGameState = CastChecked<AShooterGameState>(GameState);
	float BestScore = MIN_flt;
	int32 BestPlayer = -1;
	int32 NumBestPlayers = 0;

	for (int32 i = 0; i < MyGameState->PlayerArray.Num(); i++)
	{
		const float PlayerScore = MyGameState->PlayerArray[i]->Score;
		if (BestScore < PlayerScore)
		{
			BestScore = PlayerScore;
			BestPlayer = i;
			NumBestPlayers = 1;
		}
		else if (BestScore == PlayerScore)
		{
			NumBestPlayers++;
		}
	}

	WinnerPlayerState = (NumBestPlayers == 1) ? Cast<AShooterPlayerState>(MyGameState->PlayerArray[BestPlayer]) : NULL;
}

bool AShooterGame_FreeForAll::IsWinner(AShooterPlayerState* PlayerState) const
{
	return PlayerState && !PlayerState->IsQuitter() && PlayerState == WinnerPlayerState;
}
