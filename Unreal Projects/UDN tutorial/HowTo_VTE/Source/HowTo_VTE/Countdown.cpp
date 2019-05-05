// Fill out your copyright notice in the Description page of Project Settings.

#include "Countdown.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 렌더러블 텍스트 컴포넌트 를 만들어 카운트다운 시간을 3 초로 초기화시키면 됩니다.
	// 이러한 액터 유형에는 Ticking 이 필요치 않으니 꺼도 됩니다
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;

	CountdownTime = 3;

}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();

	// 새로운 업데이트 함수로의 호출을 추가하여 ACountdown::BeginPlay 의 텍스트 표시를 초기화시키고, 
	// 초당 한 번씩 카운트다운을 진행 및 업데이트하는 타이머 설정을 해 줍시다.
	// ACountdown::ACountdown 이 아닌 ACountdown::BeginPlay 에서 디스플레이를 업데이트하고 있는데, 
	// 언리얼 에디터 에서 변수에 설정된 값은 생성자 이후 BeginPlay 이전 할당되기 때문입니다.
	// 나중에 CountdownTime 을 에디터에 노출시킬 때, 그 값을 따라주는 것이 좋을 것입니다.
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);
	
}

// Called every frame
void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountdown::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ACountdown::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1)
	{
		//카운트 다운이 완료되었으니, 타이머를 중지시킵니다.
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

void ACountdown::CountdownHasFinished_Implementation()
{
	//특별 문구로 전환합니다.
	CountdownText->SetText(TEXT("GO!"));
}