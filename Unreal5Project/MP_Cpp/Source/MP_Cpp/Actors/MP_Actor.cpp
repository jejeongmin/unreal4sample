// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MP_Actor.h"

// Sets default values
AMP_Actor::AMP_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bNetLoadOnClient = true;
	bReplicates = true;
	bAlwaysRelevant = true;

	SetReplicateMovement(true);

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
		//RootComponent->SetIsReplicated(true);
	}
}

// Called when the game starts or when spawned
void AMP_Actor::BeginPlay()
{
	Super::BeginPlay();

	//if (HasAuthority())
	//{
	//	Client_PrintActorName();
	//}
}

void AMP_Actor::Client_PrintActorName_Implementation()
{
	FString	MessageString = HasAuthority() ? "Server:" : "Client:";
	MessageString += FString::Printf(TEXT(" Actor name is %s"), *GetName());

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, MessageString);
}

void AMP_Actor::Server_PrintActorName_Implementation()
{
	FString	MessageString = HasAuthority() ? "Server:" : "Client:";
	MessageString += FString::Printf(TEXT(" Actor name is %s"), *GetName());

	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Purple, MessageString);
}

/*
	이 부분은 Udemy 강의 예제가 잘못된 듯 하다.
	Server 에 의해 생성된 Pawn 이 다른 Client 에게 Replication 에 의해 동기화 될 때, Owner 가 Replication 되면서 OnRep_Owner() 가 호출되는데,
	이 때 이 Actor 는 이 Replication 을 전달 받은 클라이언트의 소유가 아니다.
	당연히 이 액터의 PlayerController 는 존재하지 않으며, GetOwner() 는 nullptr 을 반환한다.
*/
void AMP_Actor::OnRep_Owner()
{
	Super::OnRep_Owner();

	UE_LOG(LogTemp, Log, TEXT("Owner name: %s, NetRole: %s, NetRemoteRole: %s"), *GetOwner()->GetName(), *UEnum::GetValueAsString(GetLocalRole()), *UEnum::GetValueAsString(GetRemoteRole()));

	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (PC && PC->NetConnection)
	{
		// NetConnection is valid
		UE_LOG(LogTemp, Log, TEXT("Valid UNetConnection: %s"), *PC->NetConnection->GetName());
	}
	else
	{
		// NetConnection is not valid
		UE_LOG(LogTemp, Warning, TEXT("No valid UNetConnection for owner!"));
	}

	Server_PrintActorName();
}

// Called every frame
void AMP_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

