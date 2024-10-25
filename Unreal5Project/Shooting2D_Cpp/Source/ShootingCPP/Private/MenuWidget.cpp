// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

/*
	�ȱ׷��� NativeConstruct �Լ��� �ñ��ߴµ�
	���� delegate �� �ʱ�ȭ�ϱ� ���� ��ġ�� BeginPlay �ε�, �� �Լ��� Actor �� ��ӹ޾ƾ� �� �� �ִ�.
	�׷��� UserWidget Ŭ������ Actor �� ��� ���� �ʴ´�.
	�̾� ������ ������ �ϴ� ���� NativeConstruct �̴�.
*/
void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �� ��ư �Է� �̺�Ʈ�� �����ϴ� �Լ��� �����Ѵ�.
	button_Restart->OnClicked.AddDynamic(this, &UMenuWidget::Restart);
	button_Quit->OnClicked.AddDynamic(this, &UMenuWidget::Quit);
}


void UMenuWidget::Restart()
{
	// ������ �ٽ� �ε��Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

/*
	QuitGame �� ����° �Ű����� :

		���� ����Ʈ�������� ���� �����ص� �ȵ���̵� OS �� iOS �� ��׶��忡�� ���� �־
		�ٽ� ������ �� �ε� ���� �ٷ� ���� �ٽ� �� �� �ִ�.
	
		�̷��� ����̽��� OS �ý��ۿ��� ���ܵΰ� ���ุ �����ϴ� Ÿ���� EQuitPreference::Background Ÿ���̰�,
		��׶��忡 ���ܵ��� �ʰ� �����ϰ� �����ع����� Ÿ���� EQuitPreference::Quit �̴�.

	QuitGame �� �׹�° �Ű����� :

		�÷��� ���� ���� �Ӽ��� <�÷��̽����̼�4>�� ���� Ư�� �÷��������� �������� ���� ���α׷����� ���� �����ϴ� ���� �����ϴ� ��쵵 ���� �� �ִµ�
		�� ���ѿ� ���� ������(false), �ƴϸ� ������ �����ϰ� ������ ������ ������(true)�� �����ϴ� �׸��̴�.
*/
void UMenuWidget::Quit()
{
	// ���� ���� ���� ���� ������Ʈ�� �����´�.
	UWorld* currentWorld = GetWorld();

	// ���� �����Ų��.
	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(),
		EQuitPreference::Quit, false);
}