// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "./Engine/Classes/Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 무언가를 붙일 더미 루트 컴포넌트를 만듭니다
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// 카메라와 보이는 오브젝트를 만듭니다
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// 루트 컴포넌트에 카메라와 보이는 오브젝트를 붙입니다. 카메라를 이격 및 회전시킵니다.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-500.0f, 0.0f, 500.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	// 이 폰을 가장 빠른 번호의 플레이어가 조종하도록 설정합니다
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// "Grow" 액션에 따라 키우고 줄이는 것을 처리합니다
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			// 1 초에 걸쳐 두 배 크기로 키웁니다
			CurrentScale += DeltaTime;
		}
		else
		{
			// 키운 속도대로 절반으로 줄입니다
			CurrentScale -= (DeltaTime * 0.5f);
		}
		// 시작 크기 아래로 줄이거나 두 배 이상으로 키우지 않도록 합니다.
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	// "MoveX" 와 "MoveY" 축에 따라 이동을 처리합니다
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// "Grow" 키를 누르거나 뗄 때 반응합니다
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// "MoveX" 와 "MoveY" 두 이동 충의 값에 매 프레임 반응합니다
	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);

}

void AMyPawn::Move_XAxis(float AxisValue)
{
	// FMath::Clamp 를 사용하여 입력에서 얻은 값을 - 1 에서 + 1 범위로 제한시킵니다.
	// 이 예제에서는 문제가 되지 않지만, 같은 방식으로 축에 영향을 끼칠 수 있는 키가 여럿 있는 경우, 
	// 플레이어가 그 입력들을 동시에 누른다면 값이 전부 더해지게 될 것입니다.
	// 예를 들어 W 와 위 화살표 모두 1.0 스케일의 MoveX 에 매핑되어 있을 때 두 키 모두 두른다면 AxisValue 값이 2.0 이 되어, 
	// 제한시키지 않는다면 플레이어가 두 배 속력으로 움직이게 됩니다.

	// 초당 100 유닛을 앞 또는 뒤로 움직입니다
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	// 초당 100 유닛을 오른쪽 또는 왼쪽으로 움직입니다
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}
