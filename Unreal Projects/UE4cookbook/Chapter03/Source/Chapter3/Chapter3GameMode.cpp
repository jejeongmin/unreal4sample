// Fill out your copyright notice in the Description page of Project Settings.

#include "Chapter3.h"
#include "Chapter3GameMode.h"
#include "Action.h"



void AChapter3GameMode::StartPlay()
{
	/*
		UObject 의 파생 클래스는 NewObject 함수로, UActor 의 파생 클래스는 SpawnActor 함수로 생성한다.

		여기서 힙 할당 데이터를 저장하기 위해 휘발성 패키지(Transient Package)를 사용한다.
		세 번째 인수(선택 사항)은 UObject 가 메모리 관리 시스템에 의해 처리되는 방법을 나타내는 매개변수의 조합이다.
	*/
	UAction *action = NewObject<UAction>(GetTransientPackage(), UAction::StaticClass()/*, RF_* flags */);

	if (action)
	{
		action->Text = TEXT("create uobject by NewObject");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *action->Text);
	}
}