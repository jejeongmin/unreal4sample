// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSection.h"
#include "ABCharacter.h"
#include "ABItemBox.h"
#include "ABPlayerController.h"
#include "ABGameMode.h"

// Sets default values
AABSection::AABSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/Book/StaticMesh/SM_SQUARE.SM_SQUARE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(*AssetPath);
	if (SM_SQUARE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_SQUARE.Object);
	}
	else
	{
		ABLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *AssetPath);
	}

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	Trigger->SetCollisionProfileName(TEXT("ABTrigger"));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABSection::OnTriggerBeginOverlap);

	FString GateAssetPath = TEXT("/Game/Book/StaticMesh/SM_GATE.SM_GATE");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GATE(*GateAssetPath);
	if (!SM_GATE.Succeeded())
	{
		ABLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *GateAssetPath);
	}

	static FName GateSockets[] = { {TEXT("+XGate")}, {TEXT("-XGate")}, {TEXT("+YGate")}, {TEXT("-YGate")} };
	for (FName GateSocket : GateSockets)
	{
		ABCHECK(Mesh->DoesSocketExist(GateSocket));
		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		NewGate->SetStaticMesh(SM_GATE.Object);
		NewGate->SetupAttachment(RootComponent, GateSocket);
		// 제공하는 철문 애셋은 피벗이 왼쪽에 있으므로 부착하는 최종 위치는 소켓 위치로부터 Y 축으로 -80.5 만큼 이동한 지점이 된다.
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		GateMeshes.Add(NewGate);

		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("Trigger")));
		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		NewGateTrigger->SetCollisionProfileName(TEXT("ABTrigger"));
		GateTriggers.Add(NewGateTrigger);

		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABSection::OnGateTriggerBeginOverlap);
		NewGateTrigger->ComponentTags.Add(GateSocket);
	}

	bNoBattle = false;

	EnemySpawnTime = 2.0f;
	ItemBoxSpawnTime = 5.0f;
}

/*
	chapster 13

	섹션 액터는 완료 스테이트에서 시작하기 때문에 플레이를 누르면 자동으로 모든 문이 열린다.
	하지만 제작 단계에서 완료 스테이트의 상황으로 모든 문이 열리도록 제작자에게 보여진다면 더욱 편리할 것이다.
	액터에는 에디터와 연동되는 OnConstruction 이라는 특별한 함수가 설계돼 있다.
	에디터 작업에서 선택한 액터의 속성이나 트랜스폼 정보가 변경될 때 이 OnConstruction 함수가 실행된다.
*/
void AABSection::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

// Called when the game starts or when spawned
void AABSection::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
}

void AABSection::SetState(ESectionState NewState)
{
	switch (NewState)
	{
	case ESectionState::READY:
	{
		Trigger->SetCollisionProfileName(TEXT("ABTrigger"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(true);
		break;
	}
	case ESectionState::BATTLE:
	{
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}

		OperateGates(false);

		GetWorld()->GetTimerManager().SetTimer(SpawnNPCTimerHandle, FTimerDelegate::CreateUObject(this, &AABSection::OnNPCSpawn), EnemySpawnTime, false);

		GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			FVector2D RandXY = FMath::RandPointInCircle(600.0f);
			GetWorld()->SpawnActor<AABItemBox>(GetActorLocation() + FVector(RandXY, 30.0f), FRotator::ZeroRotator);
		}), ItemBoxSpawnTime, false);
		break;
	}
	case ESectionState::COMPLETE:
	{
		Trigger->SetCollisionProfileName(TEXT("NoCollision"));
		for (UBoxComponent* GateTrigger : GateTriggers)
		{
			GateTrigger->SetCollisionProfileName(TEXT("ABTrigger"));
		}

		OperateGates(true);
		break;
	}
	}

	CurrentState = NewState;
}

void AABSection::OperateGates(bool bOpen)
{
	for (UStaticMeshComponent* Gate : GateMeshes)
	{
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
	}
}

void AABSection::OnTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (CurrentState == ESectionState::READY)
	{
		SetState(ESectionState::BATTLE);
	}
}

void AABSection::OnGateTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABCHECK(OverlappedComponent->ComponentTags.Num() == 1);

	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	if (!Mesh->DoesSocketExist(SocketName))
		return;

	FVector NewLocation = Mesh->GetSocketLocation(SocketName);

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);
	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		ObjectQueryParam,
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);
		
	/*
		chapter 13

		물리엔진의 충돌을 이용해 해당 위치에 액터가 있다면 생성을 건너뛰도록 한다.
	*/
	if (!bResult)
	{
		auto NewSection = GetWorld()->SpawnActor<AABSection>(NewLocation, FRotator::ZeroRotator);
	}
	else
	{
		ABLOG(Warning, TEXT("New section area is not empty."));
	}
}

void AABSection::OnNPCSpawn()
{
	auto KeyNPC = GetWorld()->SpawnActor<ABCharacter>(GetActorLocation() + FVector::UpVector * 88.0f, FRotator::ZeroRotator);
	if (nullptr != KeyNPC)
	{
		KeyNPC->OnDestroyed.AddDynamic(this, &AABSection::OnKeyNPCDestroyed);
	}
}

void AABSection::OnKeyNPCDestroyed(AActor * DestroyedActor)
{
	auto character = Cast<ABCharacter>(DestroyedActor);
	ABCHECK(nullptr != character);

	/*
		chapter 14

		이전에 구현한 경험치의 경우 대미지를 입을 때마다 Instigator 를 검사하는 방식보다, 
		소멸될 때 LastHitBy 를 사용해 처리하는 것이 효율적이지만, 학습을 위해 두 가지 경우를 모두 예제로 만들어 보았다.
	*/
	auto ABPlayerController = Cast<AABPlayerController>(character->LastHitBy);
	ABCHECK(nullptr != ABPlayerController);

	auto ABGameMode = Cast<AABGameMode>(GetWorld()->GetAuthGameMode());
	ABCHECK(nullptr != ABGameMode);
	ABGameMode->AddScore(ABPlayerController);

	SetState(ESectionState::COMPLETE);
}
