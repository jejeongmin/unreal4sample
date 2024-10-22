// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"
#include "Components/BoxComponent.h"


AKillZone::AKillZone()
{
	PrimaryActorTick.bCanEverTick = true;

    // �ڽ� ������Ʈ�� �����ϰ� ��Ʈ ������Ʈ�� �����Ѵ�.
    boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
    SetRootComponent(boxComp);

    // �ڽ� ������Ʈ�� �����Ƽ�� ���� ���·� �����Ѵ�.
    boxComp->SetMobility(EComponentMobility::Static);

    // �ڽ��� ũ�⸦ 50, 2000, 50���� �����Ѵ�.
    boxComp->SetBoxExtent(FVector(50, 2000, 50));

    // �ڽ� ������Ʈ�� �ݸ��� �������� KillZone���� �����Ѵ�.
    boxComp->SetCollisionProfileName(TEXT("KillZone"));

}

void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

