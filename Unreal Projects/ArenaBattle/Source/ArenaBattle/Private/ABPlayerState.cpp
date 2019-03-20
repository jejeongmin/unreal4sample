// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerState.h"
#include "ABGameInstance.h"
#include "ABSaveGame.h"

AABPlayerState::AABPlayerState()
{
	CharacterLevel = 1;
	CharacterIndex = 0;
	GameScore = 0;
	GameHighScore = 0;
	Exp = 0;
	SaveSlotName = TEXT("Player1");
}

int32 AABPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 AABPlayerState::GetGameHighScore() const
{
	return GameHighScore;
}

int32 AABPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
}

int32 AABPlayerState::GetCharacterIndex() const
{
	return CharacterIndex;
}

void AABPlayerState::InitPlayerData()
{
	auto ABSaveGame = Cast<UABSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (nullptr == ABSaveGame)
	{
		ABSaveGame = GetMutableDefault<UABSaveGame>();
		// 최초에 세이브 슬롯을 생성할 때, 게임 편하게 하기 위해 초기 레벨을 5로 지정.
		ABSaveGame->Level = 5;
	}

	SetPlayerName(ABSaveGame->PlayerName);
	SetCharacterLevel(ABSaveGame->Level);
	GameScore = 0;
	GameHighScore = ABSaveGame->HighScore;
	Exp = ABSaveGame->Exp;
	CharacterIndex = ABSaveGame->CharacterIndex;
	SavePlayerData();
}

float AABPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;

	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	ABLOG(Warning, TEXT("Ratio : %f, Current : %d, Next : %d"), Result, Exp, CurrentStatData->NextExp);
	return Result;
}

bool AABPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1)
		return false;

	bool DidLevelUp = false;
	Exp = Exp + IncomeExp;
	if (Exp >= CurrentStatData->NextExp)
	{
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}

	OnPlayerStateChanged.Broadcast();
	return DidLevelUp;
}

void AABPlayerState::AddGameScore()
{
	GameScore++;
	if (GameScore >= GameHighScore)
	{
		GameHighScore = GameScore;
	}
	OnPlayerStateChanged.Broadcast();
	SavePlayerData();
}

void AABPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	ABCHECK(nullptr != ABGameInstance);

	CurrentStatData = ABGameInstance->GetABCharacterData(NewCharacterLevel);
	ABCHECK(nullptr != CurrentStatData);

	CharacterLevel = NewCharacterLevel;
}

/*
	chapter 15

	언리얼 오브젝트를 생성할 때는 NewObject 명령을 사용하며, NewObject 로 생성된 오브젝트를 더 이상
	사용하지 않으면 언리얼 실행 환경의 Garbage Collector 가 이를 탐지해 자동으로 언리얼 오브젝트를 소멸시킨다.
	따라서 NewObject 로 생성한 언리얼 오브젝트를 삭제하기 위해 delete 키워드를 사용하지 않아도 된다.

	아래 예제에서는 굳이 NewObject 로 생성하지 않고, 일반 stack 변수로 생성해도 되었으나,
	예시를 위해 이렇게 사용한 것 같다.
*/
void AABPlayerState::SavePlayerData()
{
	UABSaveGame* NewPlayerData = NewObject<UABSaveGame>();
	NewPlayerData->PlayerName = GetPlayerName();
	NewPlayerData->Level = CharacterLevel;
	NewPlayerData->Exp = Exp;
	NewPlayerData->HighScore = GameHighScore;
	NewPlayerData->CharacterIndex = CharacterIndex;

	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0))
	{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}