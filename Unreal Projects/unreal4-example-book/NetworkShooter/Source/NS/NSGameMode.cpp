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
	// �������Ʈ ĳ���͸� �⺻ �� �÷����� �����ϱ�
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
		// ���� ����
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
			GetWorld()->ServerTravel(L"/Game/FirstPersonCPP/Maps/FirstPersonExampleMap?Listen");// , false, true);	// ���� ���� ���

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
	// �� ���� �� ����
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
		else // ���� ����
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
		// ��ϵ��� ���� ���� ���� ã��
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
				// ���� ť ��ġ���� ����
				if (ToBeSpawned.Find(Character) != INDEX_NONE)
				{
					ToBeSpawned.Remove(Character);
				}
				// �׷��� ������ ���� ��ġ ����
				Character->SetActorLocation(Spawn->GetActorLocation());
				/*
					ĳ���ʹ� �̹� Ŭ���̾�Ʈ�� �������� �� �޸𸮿� �����Ʊ� ������ ���� ��ü�� �ſ� �����ϴ�.
					�ܼ��� ���� ��ġ�� ���� ����Ʈ�� ��ġ�� �����Ѵ�.
					�� ���� ������ �������� ������Ʈ�� �� ���͸� �����ϴ��� Ȯ���Ѵ�.
					�� ���� �Լ����� ���ͼ� �� �̻��� ������ ���´�.
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
			�Ʒ��� ���� ���� üũ�� �߿��� �� �ִ�.
			� ������ ANSCharacter �� �������� ���ϸ�, Ŭ���̾�Ʈ�� ĳ���Ͱ� ���� ���·� ���� �� �ִ�.
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