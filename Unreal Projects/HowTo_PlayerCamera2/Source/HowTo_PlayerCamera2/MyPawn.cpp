// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "./Engine/Classes/Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���𰡸� ���� ���� ��Ʈ ������Ʈ�� ����ϴ�
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// ī�޶�� ���̴� ������Ʈ�� ����ϴ�
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// ��Ʈ ������Ʈ�� ī�޶�� ���̴� ������Ʈ�� ���Դϴ�. ī�޶� �̰� �� ȸ����ŵ�ϴ�.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-500.0f, 0.0f, 500.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	// �� ���� ���� ���� ��ȣ�� �÷��̾ �����ϵ��� �����մϴ�
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

	// "Grow" �׼ǿ� ���� Ű��� ���̴� ���� ó���մϴ�
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			// 1 �ʿ� ���� �� �� ũ��� Ű��ϴ�
			CurrentScale += DeltaTime;
		}
		else
		{
			// Ű�� �ӵ���� �������� ���Դϴ�
			CurrentScale -= (DeltaTime * 0.5f);
		}
		// ���� ũ�� �Ʒ��� ���̰ų� �� �� �̻����� Ű���� �ʵ��� �մϴ�.
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	// "MoveX" �� "MoveY" �࿡ ���� �̵��� ó���մϴ�
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

	// "Grow" Ű�� �����ų� �� �� �����մϴ�
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// "MoveX" �� "MoveY" �� �̵� ���� ���� �� ������ �����մϴ�
	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);

}

void AMyPawn::Move_XAxis(float AxisValue)
{
	// FMath::Clamp �� ����Ͽ� �Է¿��� ���� ���� - 1 ���� + 1 ������ ���ѽ�ŵ�ϴ�.
	// �� ���������� ������ ���� ������, ���� ������� �࿡ ������ ��ĥ �� �ִ� Ű�� ���� �ִ� ���, 
	// �÷��̾ �� �Էµ��� ���ÿ� �����ٸ� ���� ���� �������� �� ���Դϴ�.
	// ���� ��� W �� �� ȭ��ǥ ��� 1.0 �������� MoveX �� ���εǾ� ���� �� �� Ű ��� �θ��ٸ� AxisValue ���� 2.0 �� �Ǿ�, 
	// ���ѽ�Ű�� �ʴ´ٸ� �÷��̾ �� �� �ӷ����� �����̰� �˴ϴ�.

	// �ʴ� 100 ������ �� �Ǵ� �ڷ� �����Դϴ�
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	// �ʴ� 100 ������ ������ �Ǵ� �������� �����Դϴ�
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