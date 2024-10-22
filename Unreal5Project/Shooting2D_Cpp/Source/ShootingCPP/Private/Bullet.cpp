// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingGameModeBase.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	// �ڽ� ������Ʈ�� ũ�⸦ �����Ѵ�.
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(boxComp);

	// �ڽ� ������Ʈ�� �ݸ��� �������� Bullet���� �����Ѵ�.
	boxComp->SetCollisionProfileName(TEXT("Bullet"));

}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// �ڽ� ������Ʈ�� �浹 ������ �̺�Ʈ�� BulletOverlap �Լ��� �����Ѵ�.
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);

}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �������� �̵��� ��ġ�� ����Ѵ�.
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed *
		DeltaTime;

	// ���� ��ġ ��ǥ�� ������ �� ��ǥ�� �ִ´�.
	SetActorLocation(newLocation);

}

// �浹 �̺�Ʈ�� �߻��� �� ������ �Լ�
void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �浹�� ���͸� AEnemyActor Ŭ������ ��ȯ�غ���.
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);

	// ����, ĳ������ ���������� �Ǿ AEnemyActor ������ ������ ���� �ִٸ�...
	if (enemy != nullptr)
	{
		// �浹�� ���͸� �����Ѵ�.
		OtherActor->Destroy();

		// ���� ����Ʈ�� �����Ѵ�.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(),	GetActorRotation());

		// ���� ���� ��带 �����´�.
		AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();

		// AShootingGameModeBase Ŭ������ ��ȯ�Ѵ�.
		AShootingGameModeBase* currentGameModeBase = Cast<AShootingGameModeBase>(currentMode);

		// ����, ���� ��� ���̽��� �����Դٸ�...
		if (currentGameModeBase != nullptr)
		{
			// ���� ��� ���̽��� ������ 1�� �߰��Ѵ�.
			currentGameModeBase->AddScore(1);
		}

	}

	// �ڱ� �ڽ��� �����Ѵ�.
	Destroy();
}
