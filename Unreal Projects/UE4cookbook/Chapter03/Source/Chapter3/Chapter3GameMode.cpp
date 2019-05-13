// Fill out your copyright notice in the Description page of Project Settings.

#include "Chapter3.h"
#include "Chapter3GameMode.h"
#include "Action.h"



void AChapter3GameMode::StartPlay()
{
	/*
		UObject �� �Ļ� Ŭ������ NewObject �Լ���, UActor �� �Ļ� Ŭ������ SpawnActor �Լ��� �����Ѵ�.

		���⼭ �� �Ҵ� �����͸� �����ϱ� ���� �ֹ߼� ��Ű��(Transient Package)�� ����Ѵ�.
		�� ��° �μ�(���� ����)�� UObject �� �޸� ���� �ý��ۿ� ���� ó���Ǵ� ����� ��Ÿ���� �Ű������� �����̴�.
	*/
	UAction *action = NewObject<UAction>(GetTransientPackage(), UAction::StaticClass()/*, RF_* flags */);

	if (action)
	{
		action->Text = TEXT("create uobject by NewObject");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *action->Text);
	}
}