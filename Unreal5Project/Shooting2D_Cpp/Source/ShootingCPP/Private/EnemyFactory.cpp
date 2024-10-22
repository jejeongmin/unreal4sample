// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include "EnemyActor.h"


AEnemyFactory::AEnemyFactory()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // ����, ����� �ð��� ������ �ð��� �����ٸ�...
    if (currentTime > delayTime)
    {
        // ����� �ð��� 0�ʷ� �ʱ�ȭ�Ѵ�.
        currentTime = 0;

        // enemy ������ �Ҵ�� �������Ʈ�� �ڽ��� ��ġ�� �����Ѵ�.
        AEnemyActor* spawnActor = GetWorld()->SpawnActor<AEnemyActor>(enemy,
            GetActorLocation(), GetActorRotation());

    }
    // �׷��� �ʴٸ�...
    else
    {
        // ���� �������� ��� �ð��� ������Ų��.
        //currentTime = currentTime + DeltaTime;
        currentTime += DeltaTime;
    }

}

