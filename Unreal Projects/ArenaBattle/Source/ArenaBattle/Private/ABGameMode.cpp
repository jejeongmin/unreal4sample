// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameMode.h"
#include "ABPawn.h"
#include "ABCharacter.h"
#include "ABPlayerController.h"
#include "ABPlayerState.h"
#include "ABGameState.h"

AABGameMode::AABGameMode()
{
	/*
		chapter 5 code

	DefaultPawnClass = AABPawn::StaticClass();
	*/
	DefaultPawnClass = ABCharacter::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
	PlayerStateClass = AABPlayerState::StaticClass();
	GameStateClass = AABGameState::StaticClass();

	ScoreToClear = 2;

	/*	
		chapter 4 code

	static ConstructorHelpers::FClassFinder<APawn> BP_PAWN_C(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C"));

	if (BP_PAWN_C.Succeeded())
	{
		DefaultPawnClass = BP_PAWN_C.Class;
	}
	*/
}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));

	/*
		chapter 14

		새롭게 생성한 ABPlayerState 클래스를 게임 모드의 PlayerStateClass 속성에 지정하면 엔진에서는 플레이어 컨트롤러가 초기화될 때
		함께 해당 클래스의 인스턴스를 생성하고 그 포인터 값을 플레이어 컨트롤러의 PlayerState 속성에 저장한다.
		플레이어 컨트롤러의 구성을 완료하는 시점은 게임 모드의 PostLogin 함수이므로 이때 함께 ABPlayerState 의 초기화도 완료해주는 것이 좋다.
	*/
	auto ABPlayerState = Cast<AABPlayerState>(NewPlayer->PlayerState);
	ABCHECK(nullptr != ABPlayerState);
	ABPlayerState->InitPlayerData();
}

void AABGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABGameState = Cast<AABGameState>(GameState);
}

void AABGameMode::AddScore(AABPlayerController* ScoredPlayer)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto ABPlayerController = Cast<AABPlayerController>(It->Get());
		if ((nullptr != ABPlayerController) && (ScoredPlayer == ABPlayerController))
		{
			ABPlayerController->AddGameScore();
			break;
		}
	}

	ABGameState->AddGameScore();

	if (GetScore() >= ScoreToClear)
	{
		ABGameState->SetGameCleared();

		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			(*It)->TurnOff();
		}

		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			const auto ABPlayerController = Cast<AABPlayerController>(It->Get());
			if (nullptr != ABPlayerController)
			{
				ABPlayerController->ShowResultUI();
			}
		}
	}
}

int32 AABGameMode::GetScore() const
{
	return ABGameState->GetTotalGameScore();
}