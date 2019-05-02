// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "BountyDashCharacter.h"
#include "Obstacle.h"
#include "BountyDashParticle.h"

#include "Components/StaticMeshComponent.h"

ACoin::ACoin()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(Mesh);
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetCollisionProfileName("OverlapAllDynamic");
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddLocalRotation(FRotator(5.0f, 0.0f, 0.0f));
}

void ACoin::MyOnActorOverlap(AActor* OverlappedActor, AActor* otherActor)
{
	// 스폰한 코인이 이미 스폰된 장애물에 겹치는 경우 스폰의 높이를 위로 올려준다.
	if (otherActor->GetClass()->IsChildOf(AObstacle::StaticClass()) && !BeingPulled)
	{
		USphereComponent* thisSphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
		USphereComponent* otherSpehre = Cast<USphereComponent>(otherActor->GetComponentByClass(USphereComponent::StaticClass()));

		if (otherSpehre)
		{
			AddActorLocalOffset(FVector(0.0f, 0.0f, (otherSpehre->GetUnscaledSphereRadius() * 2.0f) + Collider->GetUnscaledSphereRadius()));
		}
	}

	if (otherActor->GetClass()->IsChildOf(ABountyDashCharacter::StaticClass()))
	{
		ABountyDashParticle* particleSys = GetWorld()->SpawnActor<ABountyDashParticle>(ABountyDashParticle::StaticClass(), GetTransform());
		particleSys->SetKillPoint(GetKillPoint());

		ABountyDashCharacter* myChar = Cast<ABountyDashCharacter>(otherActor);
		myChar->ScoreUp();
		GetWorld()->DestroyActor(this);
	}
}