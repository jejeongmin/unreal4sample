// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

/*
	안그래도 NativeConstruct 함수가 궁금했는데
	원래 delegate 를 초기화하기 좋은 위치는 BeginPlay 인데, 이 함수는 Actor 를 상속받아야 쓸 수 있다.
	그런데 UserWidget 클래스는 Actor 를 상속 받지 않는다.
	이아 유사한 역할을 하는 것이 NativeConstruct 이다.
*/
void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 버튼 입력 이벤트에 대응하는 함수를 연결한다.
	button_Restart->OnClicked.AddDynamic(this, &UMenuWidget::Restart);
	button_Quit->OnClicked.AddDynamic(this, &UMenuWidget::Quit);
}


void UMenuWidget::Restart()
{
	// 레벨을 다시 로드한다.
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

/*
	QuitGame 의 세번째 매개변수 :

		보통 스마트폰에서는 앱을 종료해도 안드로이드 OS 나 iOS 의 백그라운드에는 남아 있어서
		다시 실행할 때 로딩 없이 바로 앱을 다시 켤 수 있다.
	
		이렇게 디바이스의 OS 시스템에는 남겨두고 실행만 종료하는 타입이 EQuitPreference::Background 타입이고,
		백그라운드에 남겨두지 않고 완전하게 종료해버리는 타입이 EQuitPreference::Quit 이다.

	QuitGame 의 네번째 매개변수 :

		플랫폼 제한 무시 속성은 <플레이스테이션4>와 같은 특정 플랫폼에서는 실행중인 앱을 프로그램에서 직접 종료하는 것을 제한하는 경우도 있을 수 있는데
		그 제한에 따를 것인지(false), 아니면 제한을 무시하고 무조건 종료할 것인지(true)를 선택하는 항목이다.
*/
void UMenuWidget::Quit()
{
	// 현재 실행 중인 월드 오브젝트를 가져온다.
	UWorld* currentWorld = GetWorld();

	// 앱을 종료시킨다.
	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(),
		EQuitPreference::Quit, false);
}