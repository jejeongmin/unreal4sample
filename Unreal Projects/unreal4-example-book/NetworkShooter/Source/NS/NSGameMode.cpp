// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "NSGameMode.h"
#include "NSHUD.h" 
#include "NSPlayerState.h" 
#include "NSSpawnPoint.h" 
#include "NSCharacter.h" 
#include "UObject/ConstructorHelpers.h"
#include "NSGameState.h"

#include "EngineUtils.h"
#include "Engine/Engine.h"

bool ANSGameMode::bInGameMenu = true;

ANSGameMode::ANSGameMode()
	: Super()
{
	// 블루프린트 캐릭터를 기본 폰 플래스로 설정하기
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerStateClass = ANSPlayerState::StaticClass();
	GameStateClass = ANSGameState::StaticClass();
	HUDClass = ANSHUD::StaticClass();

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ANSGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		for (TActorIterator<ANSSpawnPoint> Iter(GetWorld()); Iter; ++Iter)
		{
			if ((*Iter)->Team == ETeam::RED_TEAM)
			{
				RedSpawns.Add(*Iter);
			}
			else
			{
				BlueSpawns.Add(*Iter);
			}
		}
		// 서버 스폰
		APlayerController* thisCont = GetWorld()->GetFirstPlayerController();
		if (thisCont)
		{
			ANSCharacter* thisChar = Cast<ANSCharacter>(thisCont->GetPawn());
			thisChar->SetTeam(ETeam::BLUE_TEAM);
			BlueTeam.Add(thisChar);
			Spawn(thisChar);
		}

		Cast<ANSGameState>(GameState)->bInMenu = bInGameMenu;
	}
}

void ANSGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
	{
		bInGameMenu = true;
	}
}

void ANSGameMode::Tick(float DeltaSeconds)
{
	if (Role == ROLE_Authority)
	{
		APlayerController* thisCont = GetWorld()->GetFirstPlayerController();

		if (ToBeSpawned.Num() != 0)
		{
			for (auto charToSpawn : ToBeSpawned)
			{
				Spawn(charToSpawn);
			}
		}

		if (thisCont != nullptr && thisCont->IsInputKeyDown(EKeys::R))
		{
			bInGameMenu = false;
			GetWorld()->ServerTravel(L"/Game/FirstPersonCPP/Maps/FirstPersonExampleMap?Listen");// , false, true);	// 리슨 서버 방식

			Cast<ANSGameState>(GameState)->bInMenu = bInGameMenu;
		}
	}
}

void ANSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ANSCharacter* Teamless = Cast<ANSCharacter>(NewPlayer->GetPawn());
	ANSPlayerState* NPlayerState = Cast<ANSPlayerState>(NewPlayer->PlayerState);

	if (Teamless != nullptr && NPlayerState != nullptr)
	{
		Teamless->SetNSPlayerState(NPlayerState);
	}
	// 팀 지정 및 스폰
	if (Role == ROLE_Authority && Teamless != nullptr)
	{
		if (BlueTeam.Num() > RedTeam.Num())
		{
			RedTeam.Add(Teamless);
			NPlayerState->Team = ETeam::RED_TEAM;
		}
		else if (BlueTeam.Num() < RedTeam.Num())
		{
			BlueTeam.Add(Teamless);
			NPlayerState->Team = ETeam::BLUE_TEAM;
		}
		else // 팀이 같다
		{
			BlueTeam.Add(Teamless);
			NPlayerState->Team = ETeam::BLUE_TEAM;
		}

		Teamless->CurrentTeam = NPlayerState->Team;
		Teamless->SetTeam(NPlayerState->Team);
		Spawn(Teamless);
	}
}

void ANSGameMode::Spawn(class ANSCharacter* Character)
{
	if (Role == ROLE_Authority)
	{
		// 블록되지 않은 스폰 지점 찾기
		ANSSpawnPoint* thisSpawn = nullptr;
		TArray<ANSSpawnPoint*>* targetTeam = nullptr;

		if (Character->CurrentTeam == ETeam::BLUE_TEAM)
		{
			targetTeam = &BlueSpawns;
		}
		else
		{
			targetTeam = &RedSpawns;
		}

		for (auto Spawn : (*targetTeam))
		{
			if (!Spawn->GetBlocked())
			{
				// 스폰 큐 위치에서 제거
				if (ToBeSpawned.Find(Character) != INDEX_NONE)
				{
					ToBeSpawned.Remove(Character);
				}
				// 그렇지 않으면 액터 위치 설정
				Character->SetActorLocation(Spawn->GetActorLocation());
				/*
					캐릭터는 이미 클라이언트가 접속했을 때 메모리에 생성됐기 때문에 스폰 자체는 매우 간단하다.
					단순히 액터 위치를 스폰 포인트의 위치로 설정한다.
					그 다음 스폰의 오버랩을 업데이트해 새 액터를 감지하는지 확인한다.
					그 다음 함수에서 나와서 더 이상의 실행을 막는다.
				*/
				Spawn->UpdateOverlaps();
				return;
			}
		}

		if (ToBeSpawned.Find(Character) == INDEX_NONE)
		{
			ToBeSpawned.Add(Character);
		}
	}
}

void ANSGameMode::Respawn(class ANSCharacter* Character)
{
	if (Role == ROLE_Authority)
	{
		AController* thisPC = Character->GetController();
		Character->DetachFromControllerPendingDestroy();

		ANSCharacter* newChar = Cast<ANSCharacter>(GetWorld()->SpawnActor(DefaultPawnClass));

		/*
			아래와 같은 조건 체크가 중요할 수 있다.
			어떤 이유로 ANSCharacter 가 스폰되지 못하면, 클라이언트는 캐릭터가 없는 상태로 남을 수 있다.
		*/
		if (newChar)
		{
			thisPC->Possess(newChar);
			ANSPlayerState* thisPS = Cast<ANSPlayerState>(newChar->GetController()->PlayerState);

			newChar->CurrentTeam = thisPS->Team;
			newChar->SetNSPlayerState(thisPS);

			Spawn(newChar);

			newChar->SetTeam(newChar->GetNSPlayerState()->Team);
		}
	}
}