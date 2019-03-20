// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"
#include "ABHUDWidget.h"
#include "ABPlayerState.h"
#include "ABCharacter.h"
#include "ABGameplayWidget.h"
#include "ABGameplayResultWidget.h"
#include "ABGameState.h"

AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> UI_HUD_C(TEXT("/Game/Book/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UABGameplayWidget> UI_MENU_C(TEXT("/Game/Book/UI/UI_Menu.UI_Menu_C"));
	if (UI_MENU_C.Succeeded())
	{
		MenuWidgetClass = UI_MENU_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UABGameplayResultWidget> UI_RESULT_C(TEXT("/Game/Book/UI/UI_Result.UI_Result_C"));
	if (UI_RESULT_C.Succeeded())
	{
		ResultWidgetClass = UI_RESULT_C.Class;
	}
}

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

		플레이어 컨트롤러는 게임에서의 입력과 출력되는 화면을 책임진다.
		블레이어 컨트롤러에게 UI 를 배제하고 게임에게만 입력을 전달하도록 아래와 같이 명령을 내릴 수 있다.
		에디터에서 매번 뷰포트를 클릭하지 않아도 되기 때문에 테스트할 때 편리하다.
		에디터 모드일 때 한해서 아래와 같이 동작하게 코딩해두면 좋을 것 같다.
	*/
	ChangeInputMode(true);

	HUDWidget = CreateWidget<UABHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport(1);

	ResultWidget = CreateWidget<UABGameplayResultWidget>(this, ResultWidgetClass);
	ABCHECK(nullptr != ResultWidget);

	ABPlayerState = Cast<AABPlayerState>(PlayerState);
	ABCHECK(nullptr != ABPlayerState);
	HUDWidget->BindPlayerState(ABPlayerState);
	ABPlayerState->OnPlayerStateChanged.Broadcast();
}

void AABPlayerController::ShowResultUI()
{
	auto ABGameState = Cast<AABGameState>(UGameplayStatics::GetGameState(this));
	ABCHECK(nullptr != ABGameState);
	ResultWidget->BindGameState(ABGameState);

	ResultWidget->AddToViewport();
	ChangeInputMode(false);
}

void AABPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AABPlayerController::OnGamePause);

	/*
		chapter 5

		폰을 조종하기 위한 입력 로직은 폰 클래스에 구현하는 것이 일반적이다.
		하지만 언리얼 엔진의 입력 시스템은 중간에 플레이어 컨트롤러를 거쳐서 폰에 전달된다.
		만일 플레이어 컨트롤러에 특정 입력을 처리하는 코드를 구현하면
		해당 입력은 플레이어 컨트롤러에서 필터링되어 폰에 더 이상 전달되지 않는다.
	*/
	//InputComponent->BindAxis(TEXT("LeftRight"), this, &AABPlayerController::LeftRight);
	
}

void AABPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UABGameplayWidget>(this, MenuWidgetClass);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}

void AABPlayerController::LeftRight(float NewAxisValue)
{
	// do nothing!!!
}

UABHUDWidget * AABPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void AABPlayerController::NPCKill(ABCharacter* KilledNPC) const
{
	ABPlayerState->AddExp(KilledNPC->GetExp());
}

void AABPlayerController::AddGameScore() const
{
	ABPlayerState->AddGameScore();
}
