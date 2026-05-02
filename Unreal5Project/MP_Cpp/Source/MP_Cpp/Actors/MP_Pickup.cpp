// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MP_Pickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include <Interaction/MP_Player.h>
#include <Player/MP_PlayerState.h>

// Sets default values
AMP_Pickup::AMP_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bNetLoadOnClient = true;
	bReplicates = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(RootComponent);
	PickupMesh->SetIsReplicated(true);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMP_Pickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMP_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMP_Pickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (false == OtherActor->HasAuthority() && OtherActor)
	{
		return;
	}
	
	// This will only happen on the server.
	if (!OtherActor->Implements<UMP_Player>())
		return;
	
	IMP_Player* PlayerInterface = Cast<IMP_Player>(OtherActor);
	if (!PlayerInterface)
		return;
	
	IMP_Player::Execute_IncementPickupCount(OtherActor);
	IMP_Player::Execute_IncreaseHealth(OtherActor, HealthValue);		

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (!IsValid(OtherCharacter))
		return;
	
	APlayerState* PlayerState = OtherCharacter->GetPlayerState();
	AMP_PlayerState* MPPlayerState = Cast<AMP_PlayerState>(PlayerState);
	if (!IsValid(MPPlayerState))
		return;
	
	MPPlayerState->SetNumPickups(MPPlayerState->GetNumPickups() + 1);

	Destroy();
}

