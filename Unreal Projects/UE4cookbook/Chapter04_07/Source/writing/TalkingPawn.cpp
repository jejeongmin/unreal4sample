// Fill out your copyright notice in the Description page of Project Settings.

#include "TalkingPawn.h"
#include "Talker.h"
#include "Engine.h"

// Sets default values
ATalkingPawn::ATalkingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TalkCollider = CreateDefaultSubobject<UBoxComponent>("TalkCollider");
	TalkCollider->SetBoxExtent(FVector(200, 200, 100));
	TalkCollider->OnComponentBeginOverlap.AddDynamic(this, &ATalkingPawn::OnTalkOverlap);
	TalkCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ATalkingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATalkingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATalkingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATalkingPawn::OnTalkOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	/*

		아래 ImplementsInterface 가 true 를 반환한다면, 인스턴스에 맞게 선택된 언터페이스 함수를 실행하기 위해,
		우리의 IInterface 를 포함하는 특별하게 자동 생성된 함수를 실행하려고 한다.

		이것은 <IInterface>::Execute_<FunctionName> 형태의 스태틱 함수다.
		인스턴스에서 IInterface 는 ITalker 이고, 함수는 StartTalking 이기 때문에 함수는 ITalker::Execute_StartTalking() 를 실행하려고 한다.

		이 기능을 필요로 하는 이유는 블루프린트 안에 구현된 인터페이스가 실제적으로는 C++ 컴파일 시간에 설정되지 않기 때문이다.
		그래서 인터페이스가 구현됐다는 사실을 알 수 없고, 함수를 직접 호출하기 위해 블루프린트 클래스를 IInterface 인터페이스로 캐스팅할 수 없다.
	*/
	if (OtherActor->GetClass()->ImplementsInterface(UTalker::StaticClass()))
	{
		ITalker::Execute_StartTalking(OtherActor);
	}
	
}