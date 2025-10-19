// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "LyraExperienceManagerComponent.generated.h"

class ULyraExperienceDefinition;

enum class ELyraExperienceLoadState
{
	Unloaded,
	Loading,
	Loaded,
	Deactivating,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLyraExperienceLoaded, const ULyraExperienceDefinition*);

/**
 * ULyraExperienceManagerComponent
 * - �� �״��, �ش� component�� game state�� owner�� �����鼭, experience�� ���� ������ ������ �ִ� component�̴�
 * - �Ӹ� �ƴ϶�, manager��� �ܾ ���ԵǾ� �ֵ���, experience �ε� ���� ������Ʈ �� �̺�Ʈ�� �����Ѵ�
 */
UCLASS()
class LYRACLONEGAME_API ULyraExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()
	
public:

	bool IsExperienceLoaded() { return (LoadState == ELyraExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }

	/**
	 * �Ʒ��� OnExperienceLoaded�� ���ε��ϰų�, �̹� Experience �ε��� �Ϸ�Ǿ��ٸ� �ٷ� ȣ����
	 */
	void CallOrRegister_OnExperienceLoaded(FOnLyraExperienceLoaded::FDelegate&& Delegate);

public:

	UPROPERTY()
	TObjectPtr<const ULyraExperienceDefinition> CurrentExperience;

	/** Experience�� �ε� ���¸� ����͸� */
	ELyraExperienceLoadState LoadState = ELyraExperienceLoadState::Unloaded;

	/** Experience �ε��� �Ϸ�� ����, Broadcasting Delegate */
	FOnLyraExperienceLoaded OnExperienceLoaded;
};
