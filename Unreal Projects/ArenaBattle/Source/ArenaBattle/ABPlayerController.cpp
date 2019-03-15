// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPlayerController::Possess(APawn *aPawn)
{
	ABLOG_S(Warning);
	Super::Possess(aPawn);
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*
		chapter 5

		�÷��̾� ��Ʈ�ѷ��� ���ӿ����� �Է°� ��µǴ� ȭ���� å������.
		���̾� ��Ʈ�ѷ����� UI �� �����ϰ� ���ӿ��Ը� �Է��� �����ϵ��� �Ʒ��� ���� ����� ���� �� �ִ�.
		�����Ϳ��� �Ź� ����Ʈ�� Ŭ������ �ʾƵ� �Ǳ� ������ �׽�Ʈ�� �� ���ϴ�.
		������ ����� �� ���ؼ� �Ʒ��� ���� �����ϰ� �ڵ��صθ� ���� �� ����.
	*/
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*
		chapter 5

		���� �����ϱ� ���� �Է� ������ �� Ŭ������ �����ϴ� ���� �Ϲ����̴�.
		������ �𸮾� ������ �Է� �ý����� �߰��� �÷��̾� ��Ʈ�ѷ��� ���ļ� ���� ���޵ȴ�.
		���� �÷��̾� ��Ʈ�ѷ��� Ư�� �Է��� ó���ϴ� �ڵ带 �����ϸ�
		�ش� �Է��� �÷��̾� ��Ʈ�ѷ����� ���͸��Ǿ� ���� �� �̻� ���޵��� �ʴ´�.
	*/
	//InputComponent->BindAxis(TEXT("LeftRight"), this, &AABPlayerController::LeftRight);
	
}

void AABPlayerController::LeftRight(float NewAxisValue)
{
	// do nothing!!!
}