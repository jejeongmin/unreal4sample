// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
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

	/*
		chapter 13

		언리얼 엔진은 게임 진행 중에도 비동기 방식으로 에셋을 로딩하도록 FStreamableManager 라는 클래스를 제공한다.
		이 매니저 클래스는 프로젝트에서 하나만 활성화하는 것이 좋기 때문에 우리 프로젝트에서 유일한 인스턴스로 동작하는
		ABGameInstance 클래스에서 이를 멤버 변수로 선언한다.

		언리얼에서는 이와 별도로 싱글톤으로 동작하는 언리얼 오브젝트를 지정할 수 있다.
		프로젝트 설정의 일반 세팅에 있는 Default Classes 섹션의 고급 섹션에서 이를 지정할 수 있다.
	*/
	FStreamableManager StreamableManager;

private:
	UPROPERTY()
		class UDataTable* ABCharacterTable;
};
