// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LyraPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include <Components/GameFrameworkInitStateInterface.h>
#include "LyraGameplayTags.h"
#include "LyraLog.h"


/** feature name�� component �����ϱ� component�� ���� pawn extension�� ���� ���� Ȯ���� �� �ִ� */
const FName ULyraPawnExtensionComponent::NAME_ActorFeatureName("PawnExtension");

ULyraPawnExtensionComponent::ULyraPawnExtensionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

/*
	������Ʈ�� �����Ǵ� �����̴�.
*/
void ULyraPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	// �ùٸ� Actor�� ��ϵǾ����� Ȯ��:
	{
		if (!GetPawn<APawn>())
		{
			UE_LOG(LyraLog, Error, TEXT("this component has been added to a BP whose base class is not a Pawn!"));
			return;
		}
	}

	// GameFrameworkComponentManager�� InitState ����� ���� ��� ����:
	// - ����� ��ӹ޾Ҵ� IGameFrameworkInitStateInterface �޼��� RegisterInitStateFeature()�� Ȱ��
	// - �ش� �Լ��� ������ ����
	RegisterInitStateFeature();

	// ������� ���� �Լ�
	UGameFrameworkComponentManager* Manager = UGameFrameworkComponentManager::GetForActor(GetOwningActor());
}

void ULyraPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();

	// FeatureName�� NAME_None�� ������, Actor�� ��ϵ� Feature Component�� InitState ���¸� �����ϰڴٴ� �ǹ�:
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);

	// InitState_Spawned�� ���� ��ȯ:
	// - TryToChangeInitState�� �Ʒ��� ���� ����ȴ�:
	//   1. CanChangeInitState�� ���� ��ȯ ���ɼ� ���� �Ǵ�
	//   2. HandleChangeInitState�� ���� ���� ���� (Feature Component)
	//   3. BindOnActorInitStateChanged�� Bind�� Delegate�� ���ǿ� �°� ȣ���� ��
	//      - HakPawnExtensionComponent�� ���, ��� Actor�� Feature ���� ��ȭ�� ���� OnActorInitStateChanged()�� ȣ���
	ensure(TryToChangeInitState(FLyraGameplayTags::Get().InitState_Spawned));

	// �ش� �Լ��� �츮�� �������̵� �Ѵ�:
	// - �� �Լ��� ForceUpdateInitState�� ���� �������� �������ָ� �ȴ� 
	// - ���� ���� ������Ʈ ���� (���� CanChangeInitState�� HandleChangleInitState�� �������ش�)
	CheckDefaultInitialization();
}

void ULyraPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// �ռ�, OnRegister�� RegisterInitStateFeature()�� ���� ���߾�����
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}