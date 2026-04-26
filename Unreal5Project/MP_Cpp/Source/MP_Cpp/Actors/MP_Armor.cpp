// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MP_Armor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/MP_Player.h"

// Sets default values
AMP_Armor::AMP_Armor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(RootComponent);
	HeadMesh->SetIsReplicated(true);

	LeftFootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBootsMesh"));
	LeftFootMesh->SetupAttachment(RootComponent);
	LeftFootMesh->SetIsReplicated(true);

	RightFootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBootsMesh"));
	RightFootMesh->SetupAttachment(RootComponent);
	RightFootMesh->SetIsReplicated(true);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMP_Armor::BeginPlay()
{ 
	Super::BeginPlay();
	
}

// Called every frame
void AMP_Armor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMP_Armor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// 아래 if 문을 추가 하면 서버에서만 실행됨
	// BP_Armor 의 Bluprint 속성에서 replicate를 true로 설정하면 replcation 을 통해서 서버&클라 동기화 되는 것 확인 가능
	// AttachToActor 가 아닌 replication 에 의해 동기화 되는 것을 보여주기 위해 일부러 이렇게 구현함
	/*if (HasAuthority() && OtherActor && OtherActor != this)
	{
		AttachToActor(OtherActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}*/

	// Charactor 에 대한 참조를 Armor에서 직접적으로 가져오는 방법
	//ACharacter* Character = Cast<ACharacter>(OtherActor);
	//if (HasAuthority() && IsValid(Character))
	//{
	//	HeadMesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Head");
	//	LeftFootMesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Foot_L");
	//	RightFootMesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Foot_R");
	//}

	// This will only happen on the server.
	if(OtherActor->Implements<UMP_Player>())
	{
		IMP_Player* PlayerInterface = Cast<IMP_Player>(OtherActor);
		if (PlayerInterface)
		{
			USkeletalMeshComponent* PlayerMesh = PlayerInterface->Execute_GetPlayerMesh(OtherActor);

			if (PlayerMesh)
			{
				HeadMesh->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Head");
				LeftFootMesh->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Foot_L");
				RightFootMesh->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Foot_R");

				if (OtherActor->HasAuthority() && OtherActor && OtherActor != this)
				{
					PlayerInterface->Execute_GrantArmor(OtherActor, ArmorValue);
				}
				
			}			
		}
	}
}

