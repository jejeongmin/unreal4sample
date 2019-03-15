// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "ABGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FABCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FABCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 NextExp;
};

/**
 * chapter 9
 
	언리얼 엔진은 게임 앱을 관리하기 위한 용도로 게임 인스턴스라는 언리얼 오브젝트를 제공한다.
	일종의 Document class 처럼 활용할  수 있는 성격의 객체라고 이해하면 되겠다.
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UABGameInstance();

	virtual void Init() override;
	FABCharacterData* GetABCharacterData(int32 Level);

private:
	UPROPERTY()
		class UDataTable* ABCharacterTable;
};
