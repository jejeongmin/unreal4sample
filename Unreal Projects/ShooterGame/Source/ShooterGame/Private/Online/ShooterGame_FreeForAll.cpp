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

	���� �� �ְ� ���� ȹ���� ����� winer �� �����Ѵ�.
	TDM �� winer team �� �����ϴ� �Ϳ� ���� �̰��� �� ������ WinnerPlayerState �� �����Ѵ�.
	�Ƹ� �̰� �� �Լ��� ��ȯ���� void �� �����ΰ�����.
	�����ڰ� �����ϴ� ��쿡�� �ٸ� ������ ������� �ʰ� ���ڸ� ������ �ʰ� �⺻ �����Ǿ� �ִ�.
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
